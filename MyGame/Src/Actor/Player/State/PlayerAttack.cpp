#include "PlayerAttack.h"
#include "../../../GameSystem/InputSystem/InputSystem.h"
PlayerAttack::PlayerAttack(Player* owner)
	:PlayerState::PlayerState(owner)
{
	
}

void PlayerAttack::Update(float deltaTime)
{
	if (owner_->GetMesh()->IsEndMotion()) {
		owner_->ChangeState(PlayerState::Idle);
		return;
	}
	int time = owner_->GetMesh()->MotionEndTime() - 40.0f;
	if (InputSystem::ButtonTrigger(InputSystem::Button::B) && time < owner_->GetMesh()->MotionTime()) {
		switch (combo_) {
			case 0:
				owner_->ChangeMotion(Player::Combo2, false, 1.5f);
				break;
			case 1:
				owner_->ChangeMotion(Player::Combo3, false, 1.5f);
				break;
			default:
				break;
		}
		combo_++;
	}
}

void PlayerAttack::Enter()
{
	owner_->SetAttack(true);
	owner_->ChangeMotion(Player::Attack, false,1.5f);
	combo_ = 0;
}

void PlayerAttack::Exit()
{
	owner_->SetAttack(false);
}

void PlayerAttack::SetID(int id)
{
	stateID = id;
}

int PlayerAttack::GetID()
{
	return stateID;
}
