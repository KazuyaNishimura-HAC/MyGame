#include "SwordEnemy2Guard.h"
SwordEnemy2Guard::SwordEnemy2Guard(SwordEnemy2* owner)
    :SwordEnemy2State(owner)
{
}

void SwordEnemy2Guard::Update(float deltaTime)
{
    if (owner_->GetMesh()->IsEndMotion()) {
        owner_->ChangeState(EnemyState::Idle);
    }
}

void SwordEnemy2Guard::Enter()
{
    owner_->SetAttack(true);
    owner_->LookAtPlayer();
    owner_->ChangeMotion(SwordEnemy2Motion::Guard, false);
}

void SwordEnemy2Guard::Exit()
{
    owner_->SetAttack(false);
}

