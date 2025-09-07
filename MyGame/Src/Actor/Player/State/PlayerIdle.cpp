#include "PlayerIdle.h"
PlayerIdle::PlayerIdle(Player* owner)
	:PlayerState::PlayerState(owner)
{
}

void PlayerIdle::Update(float deltaTime)
{
}

void PlayerIdle::Enter()
{
	owner_->ChangeMotion(0,true);
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
