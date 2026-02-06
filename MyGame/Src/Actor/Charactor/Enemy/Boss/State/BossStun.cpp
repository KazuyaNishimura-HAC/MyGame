#include "BossStun.h"
#include "../../../../../World/IWorld.h"
#include "../../../../../GameSystem/InputSystem/InputSystem.h"
BossStun::BossStun(Boss* owner)
    :BossState::BossState(owner)
{
}

void BossStun::Update(float deltaTime)
{
    stunTimer_ += deltaTime / 60.0f;
    if (stunTimer_ >= stunDuration_) owner_->ChangeState(Idle);
    float currentBreakPt = owner_->CurrentBreakPoint();
    float maxBrekPt = owner_->MaxBreakPoint();
    float breakPt = currentBreakPt - (maxBrekPt * deltaTime / 60.0f) / stunDuration_;
    owner_->SetBreakPoint(breakPt);
}

void BossStun::Enter()
{
    stunTimer_ = 0.0f;
    //エフェクト再生
    effectHandle_ = Effect::CreateHandle(Effect::Confusion);
    EffectParam param;
    param.position = owner_->Transform().position() + GSvector3{ 0,3.0f,0 };
    Effect::SetParam(effectHandle_, param);
    owner_->ChangeMotion(BossMotion::Guard);
    owner_->SetStun(true);
}

void BossStun::Exit()
{
    Effect::Stop(effectHandle_);
    owner_->SetStun(false);
    //ブレイク値をリセット
    owner_->ResetBreakPoint();
}
