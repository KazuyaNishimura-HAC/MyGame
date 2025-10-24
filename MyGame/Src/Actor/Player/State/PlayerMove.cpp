#include "PlayerMove.h"
#include "../../../GameSystem/InputSystem/InputSystem.h"
PlayerMove::PlayerMove(Player* owner)
	:PlayerState::PlayerState(owner)
{
}

void PlayerMove::Update(float deltaTime)
{
	if (InputSystem::LeftStick() == GSvector2::zero()) owner_->ChangeState(PlayerState::Idle);
	owner_->MovePosition(deltaTime);
}

void PlayerMove::Enter()
{
	owner_->GetMesh()->ChangeMotion(1, true, 1.5f);
}

void PlayerMove::Exit()
{

}

void PlayerMove::SetID(int id)
{
	stateID = id;
}

int PlayerMove::GetID()
{
	return stateID;
}
