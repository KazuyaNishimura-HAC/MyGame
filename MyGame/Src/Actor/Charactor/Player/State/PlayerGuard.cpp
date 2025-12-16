#include "PlayerGuard.h"
#include "../../../../World/IWorld.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
PlayerGuard::PlayerGuard(Player* owner)
    :PlayerState::PlayerState(owner)
{
}

void PlayerGuard::Update(float deltaTime)
{
    parryTimer_ -= deltaTime / 60.0f;
    //パリィ可能時間が切れたら無効化
    if (owner_->CanUseParry() && parryTimer_ <= 0.0f) {
        owner_->SetParryEnable(false);
    }
    //万が一違うモーションが流れていたら再度ガードモーションに
    if (owner_->GetMesh()->IsEndMotion()) {
        owner_->ChangeMotion(PlayerMotion::Guard);
    }
    if (InputSystem::ButtonDetach(InputSystem::Button::LShoulder)) {
        owner_->ChangeState(PlayerState::Idle);
    }
}

void PlayerGuard::Enter()
{
    owner_->SetGuard(true);
    owner_->SetParryEnable(true);
    parryTimer_ = parryDuration_;
    owner_->ChangeMotion(PlayerMotion::Guard);
}

void PlayerGuard::Exit()
{
    owner_->SetGuard(false);
    owner_->SetParryEnable(false);
    owner_->ResetGuardHealTime();
}

