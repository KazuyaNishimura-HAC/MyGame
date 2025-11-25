#include "PlayerParry.h"
#include "../../../../World/IWorld.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
PlayerParry::PlayerParry(Player* owner)
    :PlayerState::PlayerState(owner)
{
    //イベントの追加
    owner_->GetMesh()->AddEvent(PlayerMotion::ParryATK, 0, [=] {Attack(0); });
    owner_->GetMesh()->AddEvent(PlayerMotion::ParryATK, 18, [=] {Attack(1); });
    owner_->GetMesh()->AddEvent(PlayerMotion::ParryATK, 30, [=] {Attack(2); });
    owner_->GetMesh()->AddEvent(PlayerMotion::ParryATK, 75, [=] {Attack(3); });
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

void PlayerParry::Attack(int count)
{
    GSuint atkHandle = gsPlayEffectEx(Effect::Slash, nullptr);
    effectParams[count].handle = atkHandle;
    Effect::SetEffectParam(effectParams[count], owner_->Transform());
    owner_->TestAttack();
}
