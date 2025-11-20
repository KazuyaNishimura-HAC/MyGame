#include "PlayerParry.h"
#include "../../../../World/IWorld.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
PlayerParry::PlayerParry(Player* owner)
    :PlayerState::PlayerState(owner)
{
}

void PlayerParry::Update(float deltaTime)
{
    if (owner_->GetMesh()->IsEndMotion())isParryAttack_ = false;

    if (!isParryAttack_ && owner_->IsTimeScaleDefault()) {
        owner_->ChangeState(PlayerState::Idle);
        return;
    }
    //ボタンが押されたらパリィ攻撃可能
    if (!isParryAttack_ && InputSystem::ButtonTrigger(InputSystem::Button::B)) {
        owner_->SetTimeScale(1.0f);
        owner_->ChangeMotion(PlayerMotion::ParryATK,false,1.5f);
        isParryAttack_ = true;
    }
}

void PlayerParry::Enter()
{
    owner_->ChangeMotion(PlayerMotion::ParrySuccess, false, 1.5f,30.0f);
    owner_->SetTimeScale(0.2f, waitTime_);
    owner_->SetParry(true);
    owner_->SetInvincible(true);
}

void PlayerParry::Exit()
{
    owner_->SetTimeScale(1.0f);
    owner_->SetParry(false);
    owner_->SetInvincible(false);
    isParryAttack_ = false;
}
