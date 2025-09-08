#include "PlayerAttack.h"
#include "../../../GameSystem/InputSystem/InputSystem.h"
PlayerAttack::PlayerAttack(Player* owner)
	:PlayerState::PlayerState(owner)
{
}

void PlayerAttack::Update(float deltaTime)
{
	if (owner_->GetMesh()->IsEndMotion()) owner_->ChangeState(PlayerState::Idle);
}

void PlayerAttack::Enter()
{
	owner_->IsAttack(true);
	owner_->ChangeMotion(3, false);
}

void PlayerAttack::Exit()
{
	owner_->IsAttack(false);
}

void PlayerAttack::SetID(int id)
{
	stateID = id;
}

int PlayerAttack::GetID()
{
	return stateID;
}
