#include "BossMove.h"
BossMove::BossMove(Boss* owner)
	:BossState::BossState(owner)
{
}

void BossMove::Update(float deltaTime)
{
	owner_->Transform().position();
	owner_->MovePosition(deltaTime);
}

void BossMove::Enter()
{
	owner_->ChangeMotion(BossMotion::Run);
}

void BossMove::Exit()
{
}

void BossMove::SetID(int id)
{
	stateID = id;
}

int BossMove::GetID()
{
	return stateID;
}
