#include "PlayerAttack.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
PlayerAttack::PlayerAttack(Player* owner)
	:PlayerState::PlayerState(owner)
{
    owner_->GetMesh()->AddEvent(PlayerMotion::Attack1, 20, [=] { ComboAttack(); });
    owner_->GetMesh()->AddEvent(PlayerMotion::Attack2, 20, [=] { ComboAttack(); });
    owner_->GetMesh()->AddEvent(PlayerMotion::Attack3, 20, [=] { ComboAttack(); });
    owner_->GetMesh()->AddEvent(PlayerMotion::Attack3, 30, [=] { ComboAttack(); });
    owner_->GetMesh()->AddEvent(PlayerMotion::Attack4, 30, [=] { ComboAttack(); });
}

void PlayerAttack::Update(float deltaTime)
{
	if (owner_->GetMesh()->IsEndMotion()) {
		owner_->ChangeState(PlayerState::Idle);
		return;
	}
    //攻撃が終わる40フレーム前に攻撃処理が入ったら追加攻撃
	int time = owner_->GetMesh()->MotionEndTime() - 100.0f;
	if (InputSystem::ButtonTrigger(InputSystem::Button::B) && time < owner_->GetMesh()->MotionTime()) {
		switch (attackCount_) {
			case 0:
				owner_->ChangeMotion(PlayerMotion::Attack2, false, 1.5f);
				break;
			case 1:
				owner_->ChangeMotion(PlayerMotion::Attack3, false, 1.5f);
				break;
            case 2:
                owner_->ChangeMotion(PlayerMotion::Attack4, false, 1.5f);
                break;
			default:
				break;
		}
        attackCount_++;
	}
}

void PlayerAttack::Enter()
{
	owner_->SetAttack(true);
	owner_->ChangeMotion(PlayerMotion::Attack1, false,1.5f);
    attackCount_ = 0;
    combo_ = 0;
}

void PlayerAttack::Exit()
{
	owner_->SetAttack(false);
}

void PlayerAttack::ComboAttack()
{
    GSuint atkHandle = gsPlayEffectEx(Effect::Slash, nullptr);
    effectParams[combo_].handle = atkHandle;
    Effect::SetEffectParam(effectParams[combo_], owner_->Transform());
    owner_->TestAttack();
    combo_++;
}

