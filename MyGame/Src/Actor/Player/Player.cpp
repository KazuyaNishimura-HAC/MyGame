#include "Player.h"
#include <imgui/imgui.h>
#include "../../World/IWorld.h"
#include "../../GameSystem/Camera/Camera.h"
#include "../../GameSystem/InputSystem/InputSystem.h"
#include "../../Actor/AttackCollide.h"

#include "../../UI/PlayerUI.h"
//ステートヘッダー
#include "State/PlayerIdle.h"
#include "State/PlayerMove.h"
#include "State/PlayerDamage.h"
#include "State/PlayerDead.h"
#include "State/PlayerAttack.h"
#include "State/PlayerUltimateSkill.h"

Player::Player(IWorld* world, const GSvector3& position,Status status, GSuint mesh)
    :Charactor(world, position, status, mesh)
{
    tag_ = ActorName::Player;
    name_ = ActorName::Player;
    //ステートの追加
    states_.AddState(PlayerState::Idle, new PlayerIdle(this));
    states_.AddState(PlayerState::Move, new PlayerMove(this));
    states_.AddState(PlayerState::Damage, new PlayerDamage(this));
    states_.AddState(PlayerState::Dead, new PlayerDead(this));
    states_.AddState(PlayerState::Attack, new PlayerAttack(this));
    states_.AddState(PlayerState::Ultimate, new PlayerUltimateSkill(this));
    states_.ChangeState(PlayerState::Idle);

    colliderOffset_ = { 0.0f,1.0f,0.0f };
    camera_ = new CameraController(CameraController::Player);
    world_->AddCameraController(camera_);
    camera_->SetSmooth(true);
    attackCollider_ = new AttackCollide(this,1,{ 0,0,0 },colliderOffset_);
    world_->AddActor(attackCollider_);
    ui_ = new PlayerUI(this);
    world_->AddGUI(ui_);
    //イベントの追加
    mesh_->AddEvent(Motion::Attack, 30, [=] {TestAttack(); });
    mesh_->AddEvent(Motion::Combo2, 30, [=] {TestAttack(); });
    mesh_->AddEvent(Motion::Combo3, 30, [=] {TestAttack(); camera_->SetShakeValues(30.0f, 5.0f, 160.0f, 1.0f, 20.0f, { 0.1f,0.1f }, 0.0f); });
    mesh_->AddEvent(Motion::Attack, 30, [=] {TestAttack(); });
    mesh_->AddEvent(Motion::UltSkill, 45, [=] {TestAttack(); });
    mesh_->AddEvent(Motion::UltSkill, 70, [=] {TestAttack(); });
    mesh_->AddEvent(Motion::UltSkill, 90, [=] {TestAttack(); });
    mesh_->AddEvent(Motion::UltSkill, 110, [=] {TestAttack(); });
    mesh_->AddEvent(Motion::UltSkill, 130, [=] {TestAttack(); });
    mesh_->AddEvent(Motion::UltSkill, 160, [=] {TestAttack(); });
}
Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    Charactor::Update(deltaTime);

    if (InputSystem::ButtonTrigger(InputSystem::Button::B)) {
        if (!IsAttack() && CurrentState() != PlayerState::Damage) {
            states_.ChangeState(PlayerState::Attack);
            //camera_->SetShakeValues(30.0f, 1.0f, 160.0f, 1.0f, 20.0f, { 0.1f,0.1f }, 0.0f);
        }
    }
    
    if (!IsAttack() && InputSystem::ButtonTrigger(InputSystem::Button::A)) {
        states_.ChangeState(PlayerState::Ultimate);
    }
    MoveCamera(deltaTime);
    MoveAttackCollide();
    
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

void Player::TakeDamage(float damage)
{
    //無敵なら攻撃を受けない
    if (IsInvincible()) return;
    status_.hp -= damage;
    //hpが0なら死亡
    if (IsDying()) ChangeState(PlayerState::Dead);
    else ChangeState(PlayerState::Damage);
}

void Player::MovePosition(float deltaTime)
{
    GSvector2 input = InputSystem::LeftStick() * 0.1f * deltaTime;

    GSvector3 forward = CameraTransform().forward();
    GSvector3 right = CameraTransform().right();
    // Y成分は無視してXZ平面に投影
    forward.y = 0;
    right.y = 0;
    forward.normalize();
    right.normalize();

    // 入力をカメラ方向に変換
    GSvector3 moveDirection = (forward * input.y) + (right * input.x);
    moveDirection.normalize();
    //入力rawを移動の強さにする
    //float magnitude = input.magnitude();

    GSvector3 moveVector = moveDirection * 0.1f * moveSpeed_ * deltaTime;

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
    yaw = InputSystem::RightStick().x  * 3 * deltaTime;
    pitch = InputSystem::RightStick().y * 3 * deltaTime;
    cameraRotation_.y -= yaw;
    cameraRotation_.x -= pitch;
    cameraRotation_.x = CLAMP(cameraRotation_.x, 0.0f, 20.0f);

    float yawRad = DEG_TO_RAD(cameraRotation_.y);
    float pitchRad = DEG_TO_RAD(cameraRotation_.x);

    GSvector3 offset;
    offset.x = cos(pitchRad) * sin(yawRad);
    offset.y = sin(pitchRad);
    offset.z = cos(pitchRad) * cos(yawRad);

    GSvector3 cameraPos = transform_.position() + cameraOffset_ + (offset * cameraDepth_);
    GSvector3 target = transform_.position() + cameraFocusOffset_;
    
    camera_->SetView(cameraPos,target);
}

void Player::MoveAttackCollide()
{
    GSvector3 forward = transform_.forward() * 1.0f;
    //攻撃判定を追従
    attackCollider_->Transform().position(transform_.position()+ forward);
}

void Player::TestAttack()
{
    attackCollider_->IsAttack(0.01f,20);
}

//現在のカメラの方向を取得
GSvector3 Player::GetCameraDirection()
{
    return GSvector3(sin(DEG_TO_RAD(cameraRotation_.y)), sin(DEG_TO_RAD(cameraRotation_.x)), cos(DEG_TO_RAD(cameraRotation_.y))).normalized();
}

float Player::GetCameraHorizontalRadian()
{
    return DEG_TO_RAD(world_->GetCamera()->Transform().eulerAngles().y);
}

GStransform& Player::CameraTransform()
{
    return world_->GetCamera()->Transform();
}

void Player::Debug(float deltaTime)
{
    mesh_->Debug();
    ImGui::Begin("Playerstatus");
    ImGui::Value("MaxHP", status_.maxHP);
    ImGui::Value("HP", status_.hp);
    ImGui::Value("ATK", status_.atk);
    ImGui::End();
}
