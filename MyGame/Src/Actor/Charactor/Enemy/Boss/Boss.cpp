#include "Boss.h"
#include <imgui/imgui.h>
#include "../../../../World/IWorld.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
#include "../../AttackCollider.h"
#include "../../../../Graphics/Effect/Effect.h"
#include "../../../../Sound/SoundManager.h"

#include "BossMotion.h"
#include "State/BossState.h"
#include "State/BossIntro.h"
#include "State/BossIdle.h"
#include "State/BossMove.h"
#include "State/BossAttack.h"
#include "State/BossJumpAttack.h"
#include "State/BossDamage.h"
#include "State/BossParried.h"
#include "State/BossDead.h"

#include "../../../../UI/EnemyUI.h"
#include "../../../../UI/BossUI.h"
#include "../../../../GameSystem/BattleSystem/BattleManager.h"

Boss::Boss(IWorld* world, float groupID, const GSvector3& position, const GSvector3& rotate, Status status, GSuint mesh)
    :Enemy(world,groupID, position, rotate, status, mesh)
{
    name_ = ActorName::Boss;
    //ステートの追加
    states_.AddState(BossState::Intro, new BossIntro(this));
    states_.AddState(BossState::Idle, new BossIdle(this));
    states_.AddState(BossState::Move, new BossMove(this));
    states_.AddState(BossState::Attack, new BossAttack(this));
    states_.AddState(BossState::JumpAttack, new BossJumpAttack(this));
    states_.AddState(BossState::Damage, new BossDamage(this));
    states_.AddState(BossState::Parried, new BossParried(this));
    states_.AddState(BossState::Dead, new BossDead(this));
    states_.ChangeState(BossState::Idle);
    collider_ = BoundingSphere(1);
    attackCollider_->SetRadius(1.5f);

    ui_ = new EnemyUI(world_, this);
    world_->AddGUI(ui_);

    bossUI_ = new BossUI(world,this);
    world_->AddGUI(bossUI_);
    SetVisible(false);
    //ブレイク値を高めに設定
    SetMaxBreakPoint(200);
    
}

Boss::~Boss()
{
    if (battleManager_ != nullptr) battleManager_->BossDeadMessage();
    ui_->End();
    ui_ = nullptr;
    bossUI_->End();
    bossUI_ = nullptr;
}


void Boss::Update(float deltaTime)
{
    Enemy::Update(deltaTime);
    if (!IsDying()) Effect::LoopEffectParam(EffectParam(effectHandles_[Effect::Aura], { 0,1,0 }, {}, { 1.5f,1.5f,1.5f }, { 1,1,1,1 }, 0.5f), transform_);

    if (!IsBattleMode()) return;
    float dist = GSvector3::distance(player_->Transform().position(),transform_.position());
    //確率でジャンプ攻撃
    if (!IsAttack() && dist > 5 && GetCurrentHealth() < 750) {
        float random = 0;
        if (randomTimer_ < 0.0f) {
            random = gsRand(1, 4);
            randomTimer_ = randomDuration_;
        }
        else {
            randomTimer_ -= deltaTime / 60.0f;
        }
        if(random == 1) ChangeState(BossState::JumpAttack);
    }
    //基底クラスの処理を実行
    if (!IsCurrentState(BossState::JumpAttack)) {
        attackCollider_->SetRadius(1.5f);
        MoveAttackCollide(1.5f);
    }
    else {
        attackCollider_->SetRadius(3.0f);
        MoveAttackCollide(0);
    }
}

void Boss::LateUpdate(float deltaTime)
{
    Enemy::LateUpdate(deltaTime);
}

void Boss::Draw() const
{
    if (!IsVisible()) return;
    Enemy::Draw();
    //手につけるモデルとボーンID
    mesh_->WeaponDraw(Model::GreatSword,47);
}

void Boss::React(Actor& other)
{
    if (other.GetName() != ActorName::Player) return;
    if (IsCurrentState(BossState::Damage) || IsAttack()) return;

    ChangeState(BossState::Attack);
}

void Boss::OnParryHit(const GSvector3& position)
{
    AddBreakPoint(50);
    ChangeState(BossState::Parried);
    Knockback(0.2f, position);
}

void Boss::HitAttackCollider(const AttackInfo& atkInfo)
{
    //死亡しているならreturn
    if (IsDying()) return;
    EffectParam param;
    param.handle = Effect::Hit;
    param.position = transform_.position() + GSvector3{ 0,1,0 };
    param.scale = { 0.5f,0.5f,0.5f };
    Effect::SetEffectParam(param);
    SoundManager::PlaySE(Sound::Hit);
    SetHitReactTime();
    AddBreakPoint(2);
    TakeDamage(atkInfo.damage);
    //hpが0なら死亡
    if (IsDying()) ChangeState(BossState::Dead);

    if(!IsDying() && !IsStun() && atkInfo.damage > GetDefense()) ChangeState(BossState::Damage);
}

void Boss::SetIntro(bool intro)
{
    isIntro_ = intro;
}

bool Boss::IsIntro()
{
    return isIntro_;
}

void Boss::Debug(float deltaTime)
{
    mesh_->Debug("Boss");
    ImGui::Begin("Enemystatus");
    ImGui::Value("MaxHP", status_.maxHP);
    ImGui::Value("HP", status_.hp);
    ImGui::Value("ATK", status_.attack);
    ImGui::End();
}

void Boss::BeginIntro()
{
    SetVisible(true);
    ChangeState(BossState::Intro);
    effectHandles_[Effect::Aura] = gsPlayEffectEx(Effect::Aura, nullptr);
}

void Boss::fallEvent()
{
    GSvector3 updatePos = transform_.position();
    // 上昇する（ローカル座標基準）
    transform_.translate(0.0f, -0.5f, 0.0f);
    updatePos.y = CLAMP(transform_.position().y, 0, 512);
    transform_.position(updatePos);
}

void Boss::UpDown(float value)
{
    GSvector3 bossPosition = transform_.position();
    transform_.translate(0.0f, value, 0.0f);
    bossPosition.y = CLAMP(transform_.position().y, 0, 512);
    transform_.position(bossPosition);
}

void Boss::NormalAttack()
{
    SoundManager::PlaySE(Sound::Attack);
    SpawnAttackCollider(0.5f, GetAttackPower());
}
