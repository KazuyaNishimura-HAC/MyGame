#include "PlayerDamage.h"

PlayerDamage::PlayerDamage(Player* owner)
	:PlayerState::PlayerState(owner)
{
}

void PlayerDamage::Update(float deltaTime)
{
    timer_ += (deltaTime / 60.0f);
    vignetteIntencity_ = 0.25f * (std::sin(timer_ * 10.0f) + 1.0f);
    vignetteIntencity_ = CLAMP(vignetteIntencity_, 0.0f, 0.5f);
    if (!isExecuted_ && timer_ >= effectEndTime_) isExecuted_ = true;
    //ダメージ描画
    if (!isExecuted_) {
        if (timer_ >= effectEndTime_) {
            isExecuted_ = true;
            return;
        }
        PostEffect::Instance().SetVignetteParam({ vignetteIntencity_,0.4f,0.2f,vignetteColor_ });
    }
	if (owner_->GetMesh()->IsEndMotion()) {
		owner_->ChangeState(Idle);
	}
}

void PlayerDamage::Enter()
{
	owner_->ChangeMotion(PlayerMotion::Hit, false,1,0,0,true);
    timer_ = 0.0f;
    isExecuted_ = false;
    
    effectHandle_ = Effect::CreateHandle(Effect::Hit);
    EffectParam param;
    param.position = owner_->Transform().position() + GSvector3{ 0,1,0 };
    param.scale = { 0.5f,0.5f,0.5f };
    Effect::SetParam(effectHandle_,param);
}

void PlayerDamage::Exit()
{
    //既存値に戻す
    PostEffect::Instance().SetVignetteParam({ 0.0f,0.4f,0.2f,vignetteColor_ });
}
