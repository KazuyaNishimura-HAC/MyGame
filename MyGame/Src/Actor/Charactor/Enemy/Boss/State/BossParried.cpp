#include "BossParried.h"
BossParried::BossParried(Boss* owner)
    :BossState::BossState(owner)
{
}

void BossParried::Update(float deltaTime)
{
    if (owner_->GetMesh()->IsEndMotion()) {
        owner_->ChangeState(Idle);
    }
}

void BossParried::Enter()
{
    owner_->ChangeMotion(BasicEnemyMotion::Parried, false, 1, 0, 0, true);
}

void BossParried::Exit()
{
}
