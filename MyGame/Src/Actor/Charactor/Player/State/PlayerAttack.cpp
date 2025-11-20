#include "PlayerAttack.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
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
    //攻撃が終わる40フレーム前に攻撃処理が入ったら追加攻撃
	int time = owner_->GetMesh()->MotionEndTime() - 100.0f;
	if (InputSystem::ButtonTrigger(InputSystem::Button::B) && time < owner_->GetMesh()->MotionTime()) {
		switch (combo_) {
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
		combo_++;
	}
}

void PlayerAttack::Enter()
{
	owner_->SetAttack(true);
	owner_->ChangeMotion(PlayerMotion::Attack1, false,1.5f);
	combo_ = 0;
}

void PlayerAttack::Exit()
{
	owner_->SetAttack(false);
}

