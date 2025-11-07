#include "PlayerIdle.h"
#include "../../../GameSystem/InputSystem/InputSystem.h"
PlayerIdle::PlayerIdle(Player* owner)
	:PlayerState::PlayerState(owner)
{
}

void PlayerIdle::Update(float deltaTime)
{
	if (InputSystem::LeftStick() != GSvector2::zero()) owner_->ChangeState(PlayerState::Move);
}

void PlayerIdle::Enter()
{
	owner_->ChangeMotion(Player::Idle,true);
}

void PlayerIdle::Exit()
{

}

void PlayerIdle::SetID(int id)
{
	stateID = id;
}

int PlayerIdle::GetID()
{
	return stateID;
}
