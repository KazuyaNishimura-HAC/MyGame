#include "PlayerUltimateSkill.h"
#include "../../../GameSystem/InputSystem/InputSystem.h"
#include "../../../GameSystem/Event/UltimateAnimEvent.h"
#include "../../../World/IWorld.h"
PlayerUltimateSkill::PlayerUltimateSkill(Player* owner)
	:PlayerState::PlayerState(owner)
{
	skillEvent_ = new UltimateAnimEvent(owner_->World(),InvokeType::Manual);
	owner_->World()->AddEvent(skillEvent_);
}

void PlayerUltimateSkill::Update(float deltaTime)
{
	if (owner_->GetMesh()->IsEndMotion()) {
		owner_->ChangeState(PlayerState::Idle);
		return;
	}
}

void PlayerUltimateSkill::Enter()
{
	owner_->SetAttack(true);
	owner_->SetInvincible(true);
	owner_->ChangeMotion(Player::UltSkill, false);
	//イベント発火
	skillEvent_->SetInvoke(true);
}

void PlayerUltimateSkill::Exit()
{
	owner_->SetAttack(false);
	owner_->SetInvincible(false);
}

void PlayerUltimateSkill::SetID(int id)
{
	stateID = id;
}

int PlayerUltimateSkill::GetID()
{
	return stateID;
}
