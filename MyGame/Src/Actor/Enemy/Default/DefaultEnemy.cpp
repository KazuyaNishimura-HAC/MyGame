#include "DefaultEnemy.h"
#include <imgui/imgui.h>
#include "../../../World/IWorld.h"
#include "../../../GameSystem/InputSystem/InputSystem.h"

#include "../State/EnemyState.h"
#include "../State/EnemyIdle.h"
#include "../State/EnemyMove.h"
#include "../State/EnemyAttack.h"
#include "../State/EnemyDamage.h"
#include "../State/EnemyDead.h"

DefaultEnemy::DefaultEnemy(IWorld* world, const GSvector3& position, GSuint mesh)
    :Enemy(world, position, mesh)
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
    if(GetCoolTime() <= 0)
    damageCoolTime_ -= deltaTime / 60.0f;
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

void DefaultEnemy::TakeDamage(float damage)
{
    //死亡しているならreturn
    if (CurrentState() == EnemyState::Dead) return;

    hp_ -= damage;
    //hpが0なら死亡
    if(IsDying()) ChangeState(EnemyState::Dead);
    else ChangeState(EnemyState::Damage);
}

void DefaultEnemy::Debug(float deltaTime)
{
    ImGui::Begin("Enemystatus");
    ImGui::Value("hp",hp_);
    ImGui::End();
}

void DefaultEnemy::TestAttack()
{
    attackCollider_->IsAttack(0.5f, 10);
}
