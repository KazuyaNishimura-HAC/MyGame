#include "PlayerMove.h"

PlayerMove::PlayerMove(Player* owner)
	:PlayerState::PlayerState(owner)
{
}

void PlayerMove::Update(float deltaTime)
{

}

void PlayerMove::Enter()
{
	owner_->ChangeMotion(1, true);
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
