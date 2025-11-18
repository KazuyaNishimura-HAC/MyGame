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
    if (owner_->IsParryEnable() && parryTimer_ <= 0.0f) {
        owner_->SetParryEnable(false);
    }

    if (InputSystem::ButtonDetach(InputSystem::Button::Y)) {
        owner_->ChangeState(PlayerState::Idle);
    }
}

void PlayerGuard::Enter()
{
    owner_->SetGuard(true);
    owner_->SetParryEnable(true);
    parryTimer_ = parryDuration_;
    owner_->ChangeMotion(Player::SkillCoolTime);
}

void PlayerGuard::Exit()
{
    owner_->SetGuard(false);
    owner_->SetParryEnable(false);
}

