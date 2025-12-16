#include "EnemyStun.h"
#include "../../../../World/IWorld.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
EnemyStun::EnemyStun(Enemy* owner)
    :EnemyState::EnemyState(owner)
{
}

void EnemyStun::Update(float deltaTime)
{
    stunTimer_ += deltaTime / 60.0f;
    if (stunTimer_ >= stunDuration_) owner_->ChangeState(Idle);
    float currentBreakPt = owner_->CurrentBreakPoint();
    float maxBrekPt = owner_->MaxBreakPoint();
    float breakPt = currentBreakPt - (maxBrekPt * deltaTime / 60.0f) / stunDuration_;
    owner_->SetBreakPoint(breakPt);
}

void EnemyStun::Enter()
{
    stunTimer_ = 0.0f;
    owner_->ChangeMotion(BasicEnemyMotion::Idle);
    owner_->SetStun(true);
}

void EnemyStun::Exit()
{
    owner_->SetStun(false);
    //ブレイク値をリセット
    owner_->ResetBreakPoint();
}
