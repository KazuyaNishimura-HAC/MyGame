#include "PlayerParry.h"
#include "../../../../World/IWorld.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
#include "../../../../GameSystem/Vibration/VibrationManager.h"
#include "../../../../Graphics/Effect/PostEffect.h"
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
    blurTimer_ += (deltaTime / 60.0f);
    blurIntencity_ = 0.25f * (std::sin(blurTimer_ * 6.0f) + 1.0f);
    blurIntencity_ = CLAMP(blurIntencity_, 0.0f, 0.5f);
    //制限時間もしくは攻撃モーションに切り替わったらブラーを戻す
    if (owner_->IsAttack() && blurTimer_ >= 0.8f) isExecuted_ = true;

    if (owner_->IsAttack() && owner_->GetMesh()->IsEndMotion())owner_->SetAttack(false);

    if (owner_->GetMesh()->MotionClip() == PlayerMotion::ParrySuccess && parryTimer_ < 0.0f) {
        isParryWait_ = false;
    }
    if (!isParryWait_ && !owner_->IsAttack()) {
        owner_->ChangeState(PlayerState::Idle);
        return;
    }
    //ボタンが押されたらパリィ攻撃可能
    if (isParryWait_ && InputSystem::ButtonTrigger(InputSystem::Button::B)) {
        owner_->SetTimeScale(1.0f);
        owner_->ChangeMotion(PlayerMotion::ParryATK,false,1.5f);
        //isParryAttack_ = true;
        isParryWait_ = false;
        owner_->MoveForward(1);
        owner_->SetAttack(true);
    }
    if(!isExecuted_) PostEffect::Instance().SetRadialBlurParam({ GSvector2{ 0.5f, 0.5f },blurIntencity_,8 });
}

void PlayerParry::Enter()
{
    owner_->ChangeMotion(PlayerMotion::ParrySuccess, false, 1.5f,20.0f);
    VibrationManager::SetVibration({ 1,30 }, { 1,30 });
    GSuint parryEffect = Effect::CreateHandle(Effect::ParryBreak);
    EffectParam param;
    param.position = owner_->Transform().position() + GSvector3{ 0,1,0 };
    Effect::SetParam(parryEffect,param);

    parryTimer_ = waitTime_;
    owner_->SetTimeScale(0.2f,waitTime_);
    owner_->SetParry(true);
    owner_->SetInvincible(true);
    isParryWait_ = true;
    isExecuted_ = false;
    blurIntencity_ = 0.0f;
    blurTimer_ = 0.0f;
}

void PlayerParry::Exit()
{
    owner_->SetTimeScale(1.0f);
    owner_->SetParry(false);
    owner_->SetInvincible(false);
    owner_->SetAttack(false);
    isParryAttack_ = false;
    PostEffect::Instance().SetRadialBlurParam({ GSvector2{ 0.5f, 0.5f },0.0f,8 });
}

void PlayerParry::Attack(int count)
{
    GSuint attackEffect = Effect::CreateHandle(Effect::Slash);
    Effect::SetParam(attackEffect,effectParams[count], owner_->Transform());
    owner_->NormalAttack();
}
