#include "PlayerUltimateSkill.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
#include "../../../../GameSystem/Event/UltimateAnimEvent.h"
#include "../../../../World/IWorld.h"
PlayerUltimateSkill::PlayerUltimateSkill(Player* owner)
	:PlayerState::PlayerState(owner)
{
    owner_->GetMesh()->AddEvent(PlayerMotion::UltimateSkill, 45, [=] {Attack(0); });
    owner_->GetMesh()->AddEvent(PlayerMotion::UltimateSkill, 70, [=] {Attack(1); });
    owner_->GetMesh()->AddEvent(PlayerMotion::UltimateSkill, 90, [=] {Attack(0); });
    owner_->GetMesh()->AddEvent(PlayerMotion::UltimateSkill, 110, [=] {Attack(0); });
    owner_->GetMesh()->AddEvent(PlayerMotion::UltimateSkill, 130, [=] {Attack(0); });
    owner_->GetMesh()->AddEvent(PlayerMotion::UltimateSkill, 160, [=] {Attack(2); });

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
    owner_->SetSkillPoint(0);
	owner_->ChangeMotion(PlayerMotion::UltimateSkill, false);
	//イベント発火
	skillEvent_->SetInvoke(true);
}

void PlayerUltimateSkill::Exit()
{
	owner_->SetAttack(false);
	owner_->SetInvincible(false);
}

void PlayerUltimateSkill::Attack(int count)
{
    Effect::SetEffectParam(effectParams[count], owner_->Transform());
    owner_->UltimateATK();
}
