#include "SwordEnemy2.h"
#include <imgui/imgui.h>
#include "../../../../World/IWorld.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
#include "../../AttackCollider.h"
#include "../../../../Graphics/Effect/Effect.h"
#include "../../../../Sound/SoundManager.h"

#include "SwordEnemy2Motion.h"
#include "../EnemyState/EnemyState.h"
#include "../EnemyState/EnemyIdle.h"
#include "../EnemyState/EnemyMove.h"
#include "State/SwordEnemy2Attack.h"
#include "State/SwordEnemy2Guard.h"
#include "../EnemyState/EnemyDamage.h"
#include "../EnemyState/EnemyParried.h"
#include "../EnemyState/EnemyStun.h"
#include "../EnemyState/EnemyDead.h"

#include "../../../../UI/EnemyUI.h"
#include "../../../../GameSystem/BattleSystem/BattleManager.h"

SwordEnemy2::SwordEnemy2(IWorld* world,float groupID, const GSvector3& position, const GSvector3& rotate, Status status, GSuint mesh)
    :Enemy(world, groupID, position, rotate, status, mesh)
{
    name_ = ActorName::SwordEnemy2;
    //ステートの追加
    states_.AddState(EnemyState::Idle, new EnemyIdle(this));
    states_.AddState(EnemyState::Move, new EnemyMove(this));
    states_.AddState(EnemyState::Attack, new SwordEnemy2Attack(this));
    states_.AddState(EnemyState::Damage, new EnemyDamage(this));
    states_.AddState(EnemyState::Parried, new EnemyParried(this));
    states_.AddState(EnemyState::Stun, new EnemyStun(this));
    states_.AddState(EnemyState::Dead, new EnemyDead(this));
    states_.AddState(SwordEnemy2State::Guard, new SwordEnemy2Guard(this));
    states_.ChangeState(EnemyState::Idle);
    collider_ = BoundingSphere(1);
    //攻撃処理
    mesh_->AddEvent(SwordEnemy2Motion::ChargeATK, 75, [=] {NormalAttack(); });

    ui_ = new EnemyUI(world_,this);
    world_->AddGUI(ui_);
}

SwordEnemy2::~SwordEnemy2()
{
    //バトルシステムに通知
    if(battleManager_ != nullptr) battleManager_->EnemyDeadMessage(groupID_);
    ui_->End();
    ui_ = nullptr;
}


void SwordEnemy2::Update(float deltaTime)
{
    Enemy::Update(deltaTime);
    //基底クラスの処理を実行
    MoveAttackCollide(0.8f);
    if (IsBroken() && !IsStun()) {
        ChangeState(EnemyState::Stun);
    }
}

void SwordEnemy2::LateUpdate(float deltaTime)
{
    Enemy::LateUpdate(deltaTime);
}

void SwordEnemy2::Draw() const
{
    Enemy::Draw();
}

void SwordEnemy2::React(Actor& other)
{
    if (IsStun()) return;

    if (other.GetName() == ActorName::Player && !IsCurrentState(EnemyState::Damage) && CanAttack()) {
        ChangeState(EnemyState::Attack);
    }
}

void SwordEnemy2::HitAttackCollider(const AttackInfo& atkInfo)
{
    //死亡しているならreturn
    if (IsDying()) return;
    GSuint reactEffect;
    EffectParam param;
    param.position = transform_.position() + GSvector3{ 0,1,0 };
    param.scale = { 0.5f,0.5f,0.5f };
    
    if (!IsAttack() && !IsStun()) {
        reactEffect = Effect::CreateHandle(Effect::GuardHit);
        Effect::SetParam(reactEffect, param);
        ChangeState(SwordEnemy2State::Guard);
        return;
    }
    reactEffect = Effect::CreateHandle(Effect::Hit);
    Effect::SetParam(reactEffect, param);
    SoundManager::PlaySE(Sound::Hit);
    //デフォルトでHitタイマ設定
    SetHitReactTime();
    //スタン中でないならゲージ上昇
    if (!IsStun()) {
        AddBreakPoint(5);
        Knockback(atkInfo.knockbackPower, atkInfo.hitPos);
    }
    TakeDamage(atkInfo.damage);
    
    //hpが0なら死亡
    if (IsDying()) {
        ChangeState(EnemyState::Dead);
    }
}

bool SwordEnemy2::IsGuard()
{
    return isGuard_;
}

void SwordEnemy2::SetGuard(bool guard)
{
    isGuard_ = guard;
}

void SwordEnemy2::Debug(float deltaTime)
{
    /*ImGui::Begin("Enemystatus");
    ImGui::Value("MaxHP", status_.maxHP);
    ImGui::Value("HP", status_.hp);
    ImGui::Value("ATK", status_.atk);
    ImGui::End();*/
}

void SwordEnemy2::NormalAttack()
{
    SpawnAttackCollider(GetAttackPower(), 0, 0.5f);
    GSuint attackEffect = Effect::CreateHandle(Effect::SkillSlash);
    EffectParam param;
    param.position = { 0,1,1 };
    param.scale = { 1.5f,1.5f,1.5f };
    param.speed = 1.25f;
    Effect::SetParam(attackEffect, param, transform_);
}
