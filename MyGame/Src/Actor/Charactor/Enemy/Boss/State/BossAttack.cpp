#include "BossAttack.h"
BossAttack::BossAttack(Boss* owner)
	:BossState::BossState(owner)
{
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
	owner_->ChangeMotion(BossMotion::Attack1, false);
}

void BossAttack::Exit()
{
	owner_->SetAttack(false);
}
