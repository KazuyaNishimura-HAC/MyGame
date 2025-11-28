#include "SwordEnemy1.h"
#include <imgui/imgui.h>
#include "../../../../World/IWorld.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
#include "../../AttackCollider.h"
#include "../../../../Graphics/Effect/Effect.h"

#include "SwordEnemy1Motion.h"
#include "../EnemyState/EnemyState.h"
#include "../EnemyState/EnemyIdle.h"
#include "../EnemyState/EnemyMove.h"
#include "State/SwordEnemy1Attack.h"
#include "../EnemyState/EnemyDamage.h"
#include "../EnemyState/EnemyParried.h"
#include "../EnemyState/EnemyDead.h"

#include "../../../../UI/EnemyUI.h"

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
    states_.AddState(EnemyState::Dead, new EnemyDead(this));
    states_.ChangeState(EnemyState::Idle);
    collider_ = BoundingSphere(1);
    //攻撃処理
    mesh_->AddEvent(SwordEnemy1Motion::Attack1, 30, [=] {TestAttack(); });

    ui_ = new EnemyUI(world_,this);
    world_->AddGUI(ui_);
}

SwordEnemy1::~SwordEnemy1()
{
    //バトルシステムに通知
    world_->BattleMessage(groupID_);
    ui_->End();
    ui_ = nullptr;
}


void SwordEnemy1::Update(float deltaTime)
{
    Enemy::Update(deltaTime);
    //基底クラスの処理を実行
    MoveAttackCollide(0.8f);
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
    if (other.GetName() == ActorName::Player && CurrentState() != EnemyState::Damage) {
        ChangeState(EnemyState::Attack);
    }
}

void SwordEnemy1::HitAttackCollider(const AttackInfo& atkInfo)
{
    //死亡しているならreturn
    if (IsDying()) return;

    TakeDamage(atkInfo.damage);
    //hpが0なら死亡
    if (IsDying()) {
        ChangeState(EnemyState::Dead);
    }
    else ChangeState(EnemyState::Damage);
}

void SwordEnemy1::Debug(float deltaTime)
{
    /*ImGui::Begin("Enemystatus");
    ImGui::Value("MaxHP", status_.maxHP);
    ImGui::Value("HP", status_.hp);
    ImGui::Value("ATK", status_.atk);
    ImGui::End();*/
}

void SwordEnemy1::TestAttack()
{
    SpawnAttackCollider(0.5f, GetAttackPower());
    GSuint atkHandle = gsPlayEffectEx(Effect::Slash, nullptr);
    Effect::SetEffectParam(EffectParam(atkHandle, { 0,1,1 }, { 0,0,45 }, { 1,1,1 }), transform_);
}
