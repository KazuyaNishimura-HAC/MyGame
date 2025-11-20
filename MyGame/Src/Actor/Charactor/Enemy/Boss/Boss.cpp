#include "Boss.h"
#include <imgui/imgui.h>
#include "../../../../World/IWorld.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
#include "../../AttackCollider.h"
#include "../../../../Graphics/Effect/Effect.h"

#include "BossMotion.h"
#include "State/BossState.h"
#include "State/BossIdle.h"
#include "State/BossMove.h"
#include "State/BossAttack.h"
#include "State/BossDamage.h"
#include "State/BossDead.h"

Boss::Boss(IWorld* world, const GSvector3& position, const GSvector3& rotate, Status status, GSuint mesh)
    :Enemy(world, position, rotate, status, mesh)
{
    name_ = ActorName::Boss;
    //ステートの追加
    states_.AddState(BossState::Idle, new BossIdle(this));
    states_.AddState(BossState::Move, new BossMove(this));
    states_.AddState(BossState::Attack, new BossAttack(this));
    states_.AddState(BossState::Damage, new BossDamage(this));
    states_.AddState(BossState::Dead, new BossDead(this));
    states_.ChangeState(BossState::Idle);
    collider_ = BoundingSphere(1);
    //攻撃処理
    mesh_->AddEvent(BossMotion::Attack1, 30, [=] {Attack(); });
}

Boss::~Boss()
{
}


void Boss::Update(float deltaTime)
{
    Enemy::Update(deltaTime);
    //基底クラスの処理を実行
    MoveAttackCollide();
}

void Boss::LateUpdate(float deltaTime)
{
    Enemy::LateUpdate(deltaTime);
}

void Boss::Draw() const
{
    Enemy::Draw();
}

void Boss::React(Actor& other)
{
    if (other.GetName() == ActorName::Player && CurrentState() != BossState::Damage) {
        ChangeState(BossState::Attack);
    }
}

void Boss::TakeDamage(float damage, const GSvector3& attackPos)
{
    //死亡しているならreturn
    if (CurrentState() == BossState::Dead) return;

    status_.hp -= damage;
    //hpが0なら死亡
    if (IsDying()) ChangeState(BossState::Dead);
    else ChangeState(BossState::Damage);
}

void Boss::Debug(float deltaTime)
{
    /*mesh_->Debug("Boss");
    ImGui::Begin("Enemystatus");
    ImGui::Value("MaxHP", status_.maxHP);
    ImGui::Value("HP", status_.hp);
    ImGui::Value("ATK", status_.atk);
    ImGui::End();*/
}

void Boss::Attack()
{
    SpawnAttackCollider(0.5f,status_.atk);
    GSuint atkHandle = gsPlayEffectEx(Effect::Slash, nullptr);
    Effect::SetEffectParam(EffectParam(atkHandle, { 0,1,1 }, { 0,0,45 }, { 1,1,1 }), transform_);

}
