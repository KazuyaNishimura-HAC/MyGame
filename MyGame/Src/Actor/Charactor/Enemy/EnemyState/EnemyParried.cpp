#include "EnemyParried.h"
#include "../../../../World/IWorld.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
EnemyParried::EnemyParried(Enemy* owner)
    :EnemyState::EnemyState(owner)
{
}

void EnemyParried::Update(float deltaTime)
{
    if (owner_->GetMesh()->IsEndMotion()) {
        owner_->ChangeState(Idle);
    }
}

void EnemyParried::Enter()
{
    owner_->ChangeMotion(BasicEnemyMotion::Parried, false, 1, 0, 0, true);
}

void EnemyParried::Exit()
{
}
