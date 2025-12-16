#include "PlayerParry.h"
#include "../../../../World/IWorld.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
#include "../../../../GameSystem/Vibration/VibrationManager.h"
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
    parryTimer_ -= owner_->World()->DeltaTime() / 60.0f;
    if (isParryAttack_ && owner_->GetMesh()->IsEndMotion())isParryAttack_ = false;

    if (owner_->GetMesh()->MotionClip() == PlayerMotion::ParrySuccess && parryTimer_ < 0.0f) {
        isParryWait_ = false;
    }
    if (!isParryWait_ && !isParryAttack_) {
        owner_->ChangeState(PlayerState::Idle);
        return;
    }
    //ボタンが押されたらパリィ攻撃可能
    if (isParryWait_ && InputSystem::ButtonTrigger(InputSystem::Button::B)) {
        owner_->SetTimeScale(1.0f);
        owner_->ChangeMotion(PlayerMotion::ParryATK,false,1.5f);
        isParryAttack_ = true;
        isParryWait_ = false;
    }
}

void PlayerParry::Enter()
{
    owner_->ChangeMotion(PlayerMotion::ParrySuccess, false, 1.5f,20.0f);
    VibrationManager::SetVibration({ 1,30 }, { 1,30 });
    EffectParam param;
    param.handle = Effect::ParryBreak;
    param.position = owner_->Transform().position() + GSvector3{ 0,1,0 };
    Effect::SetEffectParam(param);

    parryTimer_ = waitTime_;
    owner_->SetTimeScale(0.2f,waitTime_);
    owner_->SetParry(true);
    owner_->SetInvincible(true);
    isParryWait_ = true;
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
    Effect::SetEffectParam(effectParams[count], owner_->Transform());
    owner_->NormalAttack();
}
