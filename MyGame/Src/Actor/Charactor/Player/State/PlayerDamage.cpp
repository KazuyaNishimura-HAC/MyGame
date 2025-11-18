#include "PlayerDamage.h"

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
	owner_->ChangeMotion(Player::Hit, false,1,0,0,true);
}

void PlayerDamage::Exit()
{
}
