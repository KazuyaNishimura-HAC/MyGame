#include "BossIntro.h"
#include "../../../../../World/IWorld.h"
BossIntro::BossIntro(Boss* owner)
    :BossState::BossState(owner)
{
}

void BossIntro::Update(float deltaTime)
{
    if (waitTimer >= 0.0f) waitTimer -= deltaTime / 60.0f;
    else if (waitTimer < 0.0f && !isAction_) {
        isAction_ = true;
        owner_->ChangeMotion(BossMotion::Jump, false, 0.25f, 80.0f,0,true);
    }
    if (owner_->GetMesh()->IsEndMotion()) {
        if(count_ == 2) owner_->ChangeState(State::Idle);
        owner_->ChangeMotion(nextMotion_[count_], false);
        count_++;
    }
    owner_->fallEvent();
}

void BossIntro::Enter()
{
    owner_->ChangeMotion(BossMotion::Jump, false,0.1f,60.0f);
    owner_->SetIntro(true);
    waitTimer = 2.0f;
}

void BossIntro::Exit()
{
    owner_->SetIntro(false);
    owner_->SetBattleMode(true);
}
