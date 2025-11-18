#include "PlayerMove.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
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
	owner_->ChangeMotion(Player::Run, true, 1.5f);
}

void PlayerMove::Exit()
{

}
