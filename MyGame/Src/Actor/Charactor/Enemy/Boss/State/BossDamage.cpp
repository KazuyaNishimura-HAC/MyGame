#include "BossDamage.h"

BossDamage::BossDamage(Boss* owner)
	:BossState::BossState(owner)
{
}

void BossDamage::Update(float deltaTime)
{
	if (owner_->GetMesh()->IsEndMotion()) {
		owner_->ChangeState(Idle);
	}
}

void BossDamage::Enter()
{
	owner_->ChangeMotion(BossMotion::Hit, false,1,0,0,true);
}

void BossDamage::Exit()
{
}

void BossDamage::SetID(int id)
{
	stateID = id;
}

int BossDamage::GetID()
{
	return stateID;
}
