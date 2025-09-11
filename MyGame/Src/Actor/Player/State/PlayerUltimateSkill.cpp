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
	owner_->IsAttack(true);
	owner_->ChangeMotion(6, false);
	//ƒCƒxƒ“ƒg”­‰Î
	skillEvent_->SetInvoke(true);
}

void PlayerUltimateSkill::Exit()
{
	owner_->IsAttack(false);
}

void PlayerUltimateSkill::SetID(int id)
{
	stateID = id;
}

int PlayerUltimateSkill::GetID()
{
	return stateID;
}
