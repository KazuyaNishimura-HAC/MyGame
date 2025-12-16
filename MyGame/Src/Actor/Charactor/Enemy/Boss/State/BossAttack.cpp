#include "BossAttack.h"
#include <gslib.h>
BossAttack::BossAttack(Boss* owner)
	:BossState::BossState(owner)
{
    //攻撃処理
    owner_->GetMesh()->AddEvent(BossMotion::Attack1, 40, [=] {
        currentEffect_ = { Effect::Slash, { 0,1.5f,1 }, { 0,0,155 }, { 1.5f,1.5f,1.5f }, { 0.75f,0,0.5f,1 }, 1.5f };
        Attack();
        });
    owner_->GetMesh()->AddEvent(BossMotion::Attack2, 40, [=] {
        currentEffect_ = { Effect::Slash, { 0,1.5f,1 }, { 0,0,155 }, { 1.5f,1.5f,1.5f }, { 0.75f,0,0.5f,1 }, 1.5f };
        Attack();
        });
    owner_->GetMesh()->AddEvent(BossMotion::Attack2, 60, [=] {
        currentEffect_ = { Effect::Slash, { 0,1.5f,1 }, { 0,0,350 }, { 1.5f,1.5f,1.5f }, { 0.75f,0,0.5f,1 }, 1.5f };
        Attack();
        });
    owner_->GetMesh()->AddEvent(BossMotion::Attack3, 40, [=] {
        currentEffect_ = { Effect::GuardHit, { 0,1,1 }, { 0,0,0 }, { 1.5f,1.5f,1.5f }, { 0.75f,0,0.5f,1 }, 1.5f };
        Attack();
        });
}

void BossAttack::Update(float deltaTime)
{
	if (owner_->GetMesh()->IsEndMotion()) {
		owner_->ChangeState(BossState::Idle);
	}
}

void BossAttack::Enter()
{
	owner_->SetAttack(true);
    owner_->LookAtPlayer();
    motionIndex_ = gsRand(0, randomMotion.size() - 1);
    float atkMotion = randomMotion[motionIndex_];
	owner_->ChangeMotion(atkMotion, false);
}

void BossAttack::Exit()
{
	owner_->SetAttack(false);
}

void BossAttack::Attack()
{
    Effect::SetEffectParam(currentEffect_, owner_->Transform());
    owner_->NormalAttack();
}
