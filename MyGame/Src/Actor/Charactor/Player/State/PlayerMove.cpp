#include "PlayerMove.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
#include "../../../../World/IWorld.h"
PlayerMove::PlayerMove(Player* owner)
	:PlayerState::PlayerState(owner)
{
}

void PlayerMove::Update(float deltaTime)
{
	if (InputSystem::LeftStick() == GSvector2::zero() || owner_->World()->IsRunningEvent()) owner_->ChangeState(PlayerState::Idle);
	owner_->MovePosition(deltaTime);
}

void PlayerMove::Enter()
{
	owner_->ChangeMotion(PlayerMotion::Run, true, 1.5f);
}

void PlayerMove::Exit()
{

}
