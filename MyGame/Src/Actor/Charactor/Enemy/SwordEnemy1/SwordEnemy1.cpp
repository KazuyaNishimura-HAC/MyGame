#include "SwordEnemy1.h"
#include <imgui/imgui.h>
#include "../../../../World/IWorld.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
#include "../../AttackCollider.h"
#include "../../../../Graphics/Effect/Effect.h"
#include "../../../../Sound/SoundManager.h"

#include "SwordEnemy1Motion.h"
#include "../EnemyState/EnemyState.h"
#include "../EnemyState/EnemyIdle.h"
#include "../EnemyState/EnemyMove.h"
#include "State/SwordEnemy1Attack.h"
#include "../EnemyState/EnemyDamage.h"
#include "../EnemyState/EnemyParried.h"
#include "../EnemyState/EnemyStun.h"
#include "../EnemyState/EnemyDead.h"

#include "../../../../UI/EnemyUI.h"
#include "../../../../GameSystem/BattleSystem/BattleManager.h"

SwordEnemy1::SwordEnemy1(IWorld* world,float groupID, const GSvector3& position, const GSvector3& rotate, Status status, GSuint mesh)
    :Enemy(world, groupID, position, rotate, status, mesh)
{
    name_ = ActorName::SwordEnemy1;
    //ステートの追加
    states_.AddState(EnemyState::Idle, new EnemyIdle(this));
    states_.AddState(EnemyState::Move, new EnemyMove(this));
    states_.AddState(EnemyState::Attack, new SwordEnemy1Attack(this));
    states_.AddState(EnemyState::Damage, new EnemyDamage(this));
    states_.AddState(EnemyState::Parried, new EnemyParried(this));
    states_.AddState(EnemyState::Stun, new EnemyStun(this));
    states_.AddState(EnemyState::Dead, new EnemyDead(this));
    states_.ChangeState(EnemyState::Idle);
    collider_ = BoundingSphere(1);
    //攻撃処理
    mesh_->AddEvent(SwordEnemy1Motion::Attack1, 30, [=] {NormalAttack(); });

    ui_ = new EnemyUI(world_,this);
    world_->AddGUI(ui_);
}

SwordEnemy1::~SwordEnemy1()
{
    //バトルシステムに通知
    if(battleManager_ != nullptr) battleManager_->EnemyDeadMessage(groupID_);
    ui_->End();
    ui_ = nullptr;
}


void SwordEnemy1::Update(float deltaTime)
{
    Enemy::Update(deltaTime);
    //基底クラスの処理を実行
    MoveAttackCollide(0.8f);
    if (IsBroken() && !IsStun()) {
        ChangeState(EnemyState::Stun);
    }
}

void SwordEnemy1::LateUpdate(float deltaTime)
{
    Enemy::LateUpdate(deltaTime);
}

void SwordEnemy1::Draw() const
{
    Enemy::Draw();
}

void SwordEnemy1::React(Actor& other)
{
    if (IsStun()) return;
    if (other.GetName() == ActorName::Player && !IsCurrentState(EnemyState::Damage)) {
        ChangeState(EnemyState::Attack);
    }
}

void SwordEnemy1::HitAttackCollider(const AttackInfo& atkInfo)
{
    //死亡しているならreturn
    if (IsDying()) return;
    EffectParam param;
    param.handle = Effect::Hit;
    param.position = transform_.position() + GSvector3{ 0,1,0 };
    param.scale = { 0.5f,0.5f,0.5f };
    Effect::SetEffectParam(param);
    SoundManager::PlaySE(Sound::Hit);
    //デフォルトでHitタイマ設定
    SetHitReactTime();
    AddBreakPoint(2);
    Knockback(atkInfo.knockbackPower,atkInfo.hitPos);
    TakeDamage(atkInfo.damage);
    
    //hpが0なら死亡
    if (IsDying()) {
        ChangeState(EnemyState::Dead);
    }
    if(!IsDying() && !IsStun() && atkInfo.damage > GetDefense())ChangeState(EnemyState::Damage);
}

void SwordEnemy1::Debug(float deltaTime)
{
    /*ImGui::Begin("Enemystatus");
    ImGui::Value("MaxHP", status_.maxHP);
    ImGui::Value("HP", status_.hp);
    ImGui::Value("ATK", status_.atk);
    ImGui::End();*/
}

void SwordEnemy1::NormalAttack()
{
    SpawnAttackCollider(GetAttackPower(), 0, 0.5f);
    Effect::SetEffectParam(EffectParam(Effect::Slash, { 0,1,1 }, { 0,0,45 }, { 1,1,1 }), transform_);
}
