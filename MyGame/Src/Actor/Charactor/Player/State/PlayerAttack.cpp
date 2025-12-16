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
    if (time < owner_->GetMesh()->MotionTime()) {
        if (InputSystem::ButtonTrigger(InputSystem::Button::B)) {
            bool attackEnd = false;
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
                attackEnd = true;
                break;
            }
            //攻撃が終了していないなら前進
            if (!attackEnd) {
                owner_->UpdateDirection();
                if (owner_->IsEnemyNearby()) owner_->MoveForward(owner_->NearstEnemyDist() - 1.5f);
                else owner_->MoveForward(2);
            }
            attackCount_++;
        }
        //ガード入力ならガード
        if(InputSystem::ButtonIsPress(InputSystem::Button::LShoulder)) owner_->ChangeState(PlayerState::Guard);
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
    attackCount_ = 0;
    combo_ = 0;
}

void PlayerAttack::ComboAttack()
{
    Effect::SetEffectParam(effectParams[combo_], owner_->Transform());
    owner_->NormalAttack();
    combo_++;
}

