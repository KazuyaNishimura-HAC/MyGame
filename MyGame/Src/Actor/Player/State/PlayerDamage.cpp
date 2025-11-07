#include "PlayerDamage.h"
#include "../../../World/IWorld.h"
#include "../../../GameSystem/InputSystem/InputSystem.h"
PlayerDamage::PlayerDamage(Player* owner)
	:PlayerState::PlayerState(owner)
{
}

void PlayerDamage::Update(float deltaTime)
{
	if (owner_->GetMesh()->IsEndMotion()) {
		owner_->ChangeState(Idle);
	}
}

void PlayerDamage::Enter()
{
	owner_->ChangeMotion(Player::Hit, false);
}

void PlayerDamage::Exit()
{
}

void PlayerDamage::SetID(int id)
{
	stateID = id;
}

int PlayerDamage::GetID()
{
	return stateID;
}
