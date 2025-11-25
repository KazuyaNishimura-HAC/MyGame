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

Boss::Boss(IWorld* world, float groupID, const GSvector3& position, const GSvector3& rotate, Status status, GSuint mesh)
    :Enemy(world,groupID, position, rotate, status, mesh)
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
    attackCollider_->SetRadius(1.5f);
    //エフェクト生成（登録）
    effectHandles_[Effect::Aura] = gsPlayEffectEx(Effect::Aura, nullptr);
    //攻撃処理
    mesh_->AddEvent(BossMotion::Attack1, 40, [=] {Attack(); });
}

Boss::~Boss()
{
    world_->IsEnd(true);
}


void Boss::Update(float deltaTime)
{
    Enemy::Update(deltaTime);
    if (!IsDying()) Effect::SetEffectParam(EffectParam(effectHandles_[Effect::Aura], { 0,1,0 }, {}, { 1.5f,1.5f,1.5f }, { 1,1,1,1 }, 0.5f), transform_);
    //基底クラスの処理を実行
    MoveAttackCollide(1.5f);
}

void Boss::LateUpdate(float deltaTime)
{
    Enemy::LateUpdate(deltaTime);
}

void Boss::Draw() const
{
    Enemy::Draw();
    //手につけるモデルとボーンID
    mesh_->WeaponDraw(Model::GreatSword,47);
}

void Boss::React(Actor& other)
{
    if (other.GetName() == ActorName::Player && CurrentState() != BossState::Damage) {
        ChangeState(BossState::Attack);
    }
}

void Boss::HitAttackCollider(const AttackInfo& atkInfo)
{
    //死亡しているならreturn
    if (IsDying()) return;

    TakeDamage(atkInfo.damage);
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
    SpawnAttackCollider(0.5f, GetAttackPower());
    GSuint atkHandle = gsPlayEffectEx(Effect::Slash, nullptr);
    Effect::SetEffectParam(EffectParam(atkHandle, { 0,1,1 }, { 0,0,155 }, { 1.5f,1.5f,1.5f },{0.75f,0,0.5f,1},1.5f), transform_);

}
