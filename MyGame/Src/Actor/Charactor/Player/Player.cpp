#include "Player.h"
#include <imgui/imgui.h>
#include "../../../World/IWorld.h"
#include "../../../GameSystem/Camera/Camera.h"
#include "../../../GameSystem/InputSystem/InputSystem.h"
#include "../../../Sound/SoundManager.h"
#include "../AttackCollider.h"
#include "../../../UI/PlayerUI.h"
#include "ParryCollider.h"
#include "EnemyDetectionCollider.h"
#include "PlayerMotion.h"
//ステートヘッダー
#include "State/PlayerIdle.h"
#include "State/PlayerMove.h"
#include "State/PlayerDamage.h"
#include "State/PlayerDead.h"
#include "State/PlayerAttack.h"
#include "State/PlayerUltimateSkill.h"
#include "State/PlayerGuard.h"
#include "State/PlayerGuardBreak.h"
#include "State/PlayerParry.h"

#include "../../../GameSystem/BattleSystem/BattleManager.h"

Player::Player(IWorld* world, const GSvector3& position, const GSvector3& rotate, Status status, GSuint mesh)
    :Charactor(world, position, rotate, status, mesh)
{
    tag_ = ActorTag::Player;
    name_ = ActorName::Player;
    //ステートの追加
    states_.AddState(PlayerState::Idle, new PlayerIdle(this));
    states_.AddState(PlayerState::Move, new PlayerMove(this));
    states_.AddState(PlayerState::Damage, new PlayerDamage(this));
    states_.AddState(PlayerState::Dead, new PlayerDead(this));
    states_.AddState(PlayerState::Guard, new PlayerGuard(this));
    states_.AddState(PlayerState::GuardBreak, new PlayerGuardBreak(this));
    states_.AddState(PlayerState::Parry, new PlayerParry(this));
    states_.AddState(PlayerState::Attack, new PlayerAttack(this));
    states_.AddState(PlayerState::Ultimate, new PlayerUltimateSkill(this));
    states_.ChangeState(PlayerState::Idle);

    colliderOffset_ = { 0.0f,1.0f,0.0f };
    camera_ = new CameraController(CameraController::Player);
    world_->AddCameraController(camera_);
    camera_->SetSmooth(true);
    //各コライダー生成
    attackCollider_ = new AttackCollider(this,1,{},colliderOffset_);
    world_->AddActor(attackCollider_);
    parryCollider_ = new ParryCollider(this,2.5f,{}, colliderOffset_);
    world_->AddActor(parryCollider_);
    detectionCollider_ = new EnemyDetectionCollider(this, 4.0f, {}, colliderOffset_);
    world_->AddActor(detectionCollider_);
    //専用UI生成
    ui_ = new PlayerUI(world,this);
    world_->AddGUI(ui_);
}
Player::~Player()
{
    //プレイヤーが死んだ事を伝える
    if (battleManager_ != nullptr) {
        battleManager_->PlayerDeadMessage();
    }
    ui_->End();
    ui_ = nullptr;
    resultData_.playerDead = true;
    battleManager_->SetResultData(resultData_);
}

void Player::Update(float deltaTime)
{
    Charactor::Update(deltaTime);
    if (IsAttack()) {
        AttackMove(deltaTime);
    }
    
    resultData_.maxCombo = maxCombo_;
    battleManager_->SetResultData(resultData_);
    //死んでいるなら更新を止める
    if (IsDying()) return;
    //イベント中は入力処理を止める
    if (!world_->IsRunningEvent()) {
        if (InputSystem::ButtonTrigger(InputSystem::Button::B)) {
            //攻撃処理
            if (!IsAttack() && !IsParry() && !IsCurrentState(PlayerState::Damage)) {
                ChangeState(PlayerState::Attack);
                UpdateDirection();
                if (IsEnemyNearby()) MoveForward(NearstEnemyDist() - 1.5f);
                MoveForward(2);
            }
        }

        if (!IsParry() && IsSkillUsable() && InputSystem::RightTriggerWeight() == 1.0f) {
            ChangeState(PlayerState::Ultimate);
        }
        if (!IsAttack() && !IsParry() && InputSystem::ButtonTrigger(InputSystem::Button::LShoulder)) ChangeState(PlayerState::Guard);
        MoveCamera(deltaTime);
    }
    RegenerateGuard(deltaTime);
    MoveColliders();
}
void Player::LateUpdate(float deltaTime)
{
    Charactor::LateUpdate(deltaTime);
}
//描画
void Player::Draw()const
{
    Charactor::Draw();
    collider_.Draw();
}

void Player::React(Actor& other)
{
}

void Player::OnAttackHit()
{
    //コンボ加算
    combo_++;
    if (maxCombo_ < combo_) maxCombo_ = combo_;

    //必殺技はゲージをためない
    if (IsCurrentState(PlayerState::Ultimate)) return;
    AddSkillPoint(5);
}

void Player::HitAttackCollider(const AttackInfo& info)
{
    //無敵or死亡中なら攻撃を受けない
    if (IsInvincible() || IsDying()) return;
    
    //パリィ可能ならパリィ処理
    if (CanUseParry()) {
        camera_->SetShakeValues(30.0f, 5.0f, 160.0f, 1.0f, 5.0f, { 0.5f,0.5f }, 0.0f);
        SoundManager::PlaySE(Sound::Parry);
        parryCollider_->IsParry(true);
        //攻撃方向に身体を向ける
        transform_.lookAt(info.hitPos);
        ChangeState(PlayerState::Parry);
        resultData_.parryCount += 1;
        return;
    }
    //ガード処理
    if (IsCurrentState(PlayerState::Guard)) {
        SoundManager::PlaySE(Sound::Guard);
        GSuint guardEffect = Effect::CreateHandle(Effect::GuardHit);
        EffectParam param;
        param.position = transform_.position() + GSvector3{ 0,1,0 };
        Effect::SetParam(guardEffect,param);
        //耐久値を減らす
        ReduceGuardPoint(1);
        if (IsGuardBroken()) {
            ChangeState(PlayerState::GuardBreak);
            SoundManager::PlaySE(Sound::Parry);
        }
        else {
            ChangeMotion(PlayerMotion::GuardHit1, false, 1, 0, 0, true);
            return;
        }
    }
    SoundManager::PlaySE(Sound::Hit);
    SetHitReactTime();
    ResetCombo();
    //ダメージ処理
    TakeDamage(info.damage);
    if (IsDying()) ChangeState(PlayerState::Dead);
    else ChangeState(PlayerState::Damage);
}

void Player::MovePosition(float deltaTime)
{
    //イベント処理中はコントローラー移動をしない
    if (world_->IsRunningEvent()) return;
    GSvector2 input = InputSystem::LeftStick() * deltaTime;
    // 入力をカメラ方向に変換
    GSvector3 moveDirection = GetInputDirection();
    //入力rawを移動の強さにする
    //float magnitude = input.magnitude();

    GSvector3 moveVector = moveDirection * moveSpeed_ * deltaTime;

    //プレイヤーを滑らかに回転
    if (input != GSvector2::zero())
    {
        //向きの補間
        GSquaternion rotation =
            GSquaternion::rotateTowards(
                transform_.rotation(),
                GSquaternion::lookRotation(moveDirection), 15.0f * deltaTime);
        transform_.rotation(rotation);
    }

    // 平行移動する（ワールド基準）
    transform_.translate(moveVector, GStransform::Space::World);
}


void Player::MoveCamera(float deltaTime)
{
    float yaw = 0, pitch = 0;
    yaw = InputSystem::RightStick().x * cameraRotateSpeed_ * deltaTime;
    pitch = InputSystem::RightStick().y * cameraRotateSpeed_ * deltaTime;
    cameraRotation_.y -= yaw;
    cameraRotation_.x -= pitch;
    //上下移動の限界値
    cameraRotation_.x = CLAMP(cameraRotation_.x, -10.0f, 45.0f);

    float yawRad = DEG_TO_RAD(cameraRotation_.y);
    float pitchRad = DEG_TO_RAD(cameraRotation_.x);

    GSvector3 offset;
    offset.x = cos(pitchRad) * sin(yawRad);
    offset.y = sin(pitchRad);
    offset.z = cos(pitchRad) * cos(yawRad);

    GSvector3 cameraPos = transform_.position() + cameraOffset_ + (offset * cameraDepth_);
    GSvector3 target = transform_.position() + cameraFocusOffset_;

    camera_->SetView(cameraPos, target);
}


void Player::SetGuard(bool guard)
{
    isGuard_ = guard;
}

bool Player::IsGuard()
{
    return isGuard_;
}

void Player::SetParryEnable(bool enable)
{
    canUseParry_ = enable;
}

bool Player::CanUseParry()
{
    return canUseParry_;
}

void Player::SetParry(bool parry)
{
    isParry_ = parry;
}

bool Player::IsParry()
{
    return isParry_;
}

bool Player::IsSkillUsable()
{
    return skillPt_ >= maxSkillPt_;
}

void Player::AddSkillPoint(float point)
{
    skillPt_ += point;
    if (skillPt_ > maxSkillPt_) skillPt_ = maxSkillPt_;
}

void Player::ReduceSkillPoint(float point)
{
    skillPt_ -= point;
    if (skillPt_ < 0.0f) skillPt_ = 0.0f;
}

void Player::SetSkillPoint(float point)
{
    skillPt_ = CLAMP(point, 0, maxSkillPt_);
}

float Player::CurrentSkillPoint() const
{
    return skillPt_;
}

float Player::MaxSkillPoint() const
{
    return maxSkillPt_;
}

void Player::AddGuardPoint(float point)
{
    guardPt_ += point;
    if (guardPt_ > maxGuardPt_) guardPt_ = maxGuardPt_;
}

void Player::ReduceGuardPoint(float point)
{
    guardPt_ -= point;
    if (guardPt_ < 0.0f) guardPt_ = 0.0f;
}

void Player::ResetGuardPoint()
{
    guardPt_ = maxGuardPt_;
}

float Player::CurrentGuardPoint() const
{
    return guardPt_;
}

float Player::MaxGuardPoint() const
{
    return maxGuardPt_;
}

bool Player::IsGuardBroken() const
{
    return guardPt_ <= 0.0f;
}

void Player::SetEnemyNearby(bool flg)
{
    isEnemyNearby_ = flg;
}

bool Player::IsEnemyNearby() const
{
    return isEnemyNearby_;
}

void Player::SetTimeScale(float slowTime, float affectTime)
{
    world_->SetTimeScale(TimeScale{ slowTime,affectTime });
}

bool Player::IsTimeScaleDefault()
{
    return world_->IsTimeScaleDefault();
}

CameraController* Player::GetPlayerCamera()
{
    return camera_;
}

void Player::MoveColliders()
{
    GSvector3 forward = transform_.forward() * 1.0f;
    //攻撃判定を追従(常にプレイヤーの正面に)
    attackCollider_->Transform().position(transform_.position() + forward);
    //パリィ専用判定を追従
    parryCollider_->Transform().position(transform_.position());
    //敵検知判定を追従
    detectionCollider_->Transform().position(transform_.position());

}

bool Player::CanHealGuardPoint() const
{
    return guardHealTimer_ >= guardHealDelay_ && guardPt_ < maxGuardPt_;
}

void Player::RegenerateGuard(float deltaTime)
{
    if (IsGuard() || IsAttack()) return;
    if (CanHealGuardPoint()) {
        //全回復まで2.5秒
        float healRate = maxGuardPt_ / 2.5f;
        AddGuardPoint( healRate * (deltaTime / 60.0f));
        return;
    }
    //タイマー加算
    guardHealTimer_ += deltaTime / 60.0f;
}

void Player::NormalAttack()
{
    SoundManager::PlaySE(Sound::Attack);
    camera_->SetShakeValues(10.0f, 5.0f, 160.0f, 1.0f, 5.0f, { 0.25f,0.25f }, 0.0f);
    SpawnAttackCollider(GetAttackPower(), 0.1f, 0.01f);
    resultData_.totalDamage += GetAttackPower();
}

void Player::UltimateATK()
{
    float attack = GetAttackPower() * 3.0f;
    camera_->SetShakeValues(10.0f, 5.0f, 160.0f, 1.0f, 5.0f, { 0.5f,0.5f }, 0.0f);
    SpawnAttackCollider(attack, 0.1f, 0.01f);
    resultData_.totalDamage += attack;
}

bool Player::IsDrawGuardBreakUI() const
{
    return guardPt_ < maxGuardPt_;
}

void Player::ResetGuardHealTime()
{
    guardHealTimer_ = 0.0f;
}

void Player::AttackMove(float deltaTime)
{
    float smoothTime = 5.0f;
    float maxSpeed = 100.0f ;
    GSvector3 pos = GSvector3::smoothDamp(transform_.position(), forwardPosition_, velocity_, smoothTime, maxSpeed, deltaTime);
    transform_.position(pos);
}

void Player::MoveForward(float value)
{
    forwardPosition_ = transform_.position() + (transform_.forward() * value);
}

GSvector3 Player::GetInputDirection() const
{
    GSvector2 input = InputSystem::LeftStick() * world_->DeltaTime();
    GSvector3 forwards = CameraTransform().forward();
    GSvector3 right = CameraTransform().right();
    // Y成分は無視してXZ平面に投影
    forwards.y = 0;
    right.y = 0;
    forwards.normalize();
    right.normalize();

    // 入力をカメラ方向に変換
    GSvector3 moveDirection = (forwards * input.y) + (right * input.x);
    moveDirection.normalize();

    //入力がないなら0を返す
    if (input == GSvector2::zero()) return GSvector3::zero();

    return moveDirection;
}

void Player::SetNearbyEnemyPos(GSvector3 position)
{
    nearbyEnemyPos_ = position;
}

float Player::NearstEnemyDist() const
{
    return GSvector3::distance(transform_.position(),nearbyEnemyPos_);
}

void Player::UpdateDirection()
{
    //周辺に敵がいるなら敵を見る
    if (IsEnemyNearby()) {
        transform_.lookAt(nearbyEnemyPos_);
    }
    else {
        // 入力方向を取得
        GSvector3 moveDirection = GetInputDirection();
        //スティック入力があればその方向に向く
        if (InputSystem::LeftStick() != GSvector2::zero())
        {
            transform_.rotation(GSquaternion::lookRotation(moveDirection));
        }
    }
}

int Player::GetCurrentCombo() const
{
    return combo_;
}

int Player::GetMaxCombo() const
{
    return maxCombo_;
}

void Player::ResetCombo()
{
    combo_ = 0;
}

//現在のカメラの方向を取得
GSvector3 Player::GetCameraDirection() const
{
    return GSvector3(sin(DEG_TO_RAD(cameraRotation_.y)), sin(DEG_TO_RAD(cameraRotation_.x)), cos(DEG_TO_RAD(cameraRotation_.y))).normalized();
}
float Player::GetCameraHorizontalRadian()
{
    return DEG_TO_RAD(world_->GetCamera()->Transform().eulerAngles().y);
}

GStransform& Player::CameraTransform() const
{
    return world_->GetCamera()->Transform();
}

void Player::Debug(float deltaTime)
{
    mesh_->Debug("Player");
    ImGui::Begin("Playerstatus");
    ImGui::Value("MaxHP", GetMaxHealth());
    ImGui::Value("HP", GetCurrentHealth());
    ImGui::Value("ATK", GetAttackPower());
    ImGui::Value("isATK", IsAttack());
    ImGui::Value("isGuard", IsGuard());
    ImGui::Value("canUseParry", CanUseParry());
    ImGui::Value("isParrying", IsParry());
    ImGui::Value("isDying", IsDying());
    ImGui::End();
}
