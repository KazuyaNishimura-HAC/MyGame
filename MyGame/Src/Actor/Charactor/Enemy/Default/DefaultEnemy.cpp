#include "DefaultEnemy.h"
#include <imgui/imgui.h>
#include "../../../../World/IWorld.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
#include "../../AttackCollider.h"
#include "../../../../Graphics/Effect/Effect.h"

#include "../State/EnemyState.h"
#include "../State/EnemyIdle.h"
#include "../State/EnemyMove.h"
#include "../State/EnemyAttack.h"
#include "../State/EnemyDamage.h"
#include "../State/EnemyDead.h"

DefaultEnemy::DefaultEnemy(IWorld* world, const GSvector3& position, const GSvector3& rotate, Status status, GSuint mesh)
    :Enemy(world, position, rotate, status, mesh)
{
    name_ = ActorName::DefaultEnemy;
    //ステートの追加
    states_.AddState(EnemyState::Idle, new EnemyIdle(this));
    states_.AddState(EnemyState::Move, new EnemyMove(this));
    states_.AddState(EnemyState::Attack, new EnemyAttack(this));
    states_.AddState(EnemyState::Damage, new EnemyDamage(this));
    states_.AddState(EnemyState::Dead, new EnemyDead(this));
    states_.ChangeState(EnemyState::Idle);
    collider_ = BoundingSphere(1);
    //攻撃処理
    mesh_->AddEvent(2, 30, [=] {TestAttack(); });
}

DefaultEnemy::~DefaultEnemy()
{
}


void DefaultEnemy::Update(float deltaTime)
{
    Enemy::Update(deltaTime);
    //基底クラスの処理を実行
    MoveAttackCollide();
}

void DefaultEnemy::LateUpdate(float deltaTime)
{
    Enemy::LateUpdate(deltaTime);
}

void DefaultEnemy::Draw() const
{
    Enemy::Draw();
}

void DefaultEnemy::React(Actor& other)
{
    if (other.GetName() == ActorName::Player && CurrentState() != EnemyState::Damage) {
        ChangeState(EnemyState::Attack);
    }
}

void DefaultEnemy::TakeDamage(float damage, const GSvector3& attackPos)
{
    //死亡しているならreturn
    if (CurrentState() == EnemyState::Dead) return;

    status_.hp -= damage;
    //hpが0なら死亡
    if(IsDying()) ChangeState(EnemyState::Dead);
    else ChangeState(EnemyState::Damage);
}

void DefaultEnemy::Debug(float deltaTime)
{
    ImGui::Begin("Enemystatus");
    ImGui::Value("MaxHP", status_.maxHP);
    ImGui::Value("HP", status_.hp);
    ImGui::Value("ATK", status_.atk);
    ImGui::End();
}

void DefaultEnemy::TestAttack()
{
    attackCollider_->IsAttack(0.5f, 10);
    GSuint atkHandle = gsPlayEffectEx(Effect::Slash, nullptr);
    Effect::SetEffectParam(EffectParam(atkHandle, { 0,1,1 }, { 0,0,45 }, { 1,1,1 }), transform_);
}
