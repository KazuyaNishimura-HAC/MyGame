#include "SwordEnemy1Attack.h"
SwordEnemy1Attack::SwordEnemy1Attack(SwordEnemy1* owner)
	:SwordEnemy1State(owner)
{
}

void SwordEnemy1Attack::Update(float deltaTime)
{
	if (owner_->GetMesh()->IsEndMotion()) {
		owner_->ChangeState(EnemyState::Idle);
	}
}

void SwordEnemy1Attack::Enter()
{
	owner_->SetAttack(true);
    owner_->LookAtPlayer();
	owner_->ChangeMotion(SwordEnemy1Motion::Attack1, false);
}

void SwordEnemy1Attack::Exit()
{
	owner_->SetAttack(false);
    owner_->SetCoolTime();
}

