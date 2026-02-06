#include "SwordEnemy2Attack.h"
SwordEnemy2Attack::SwordEnemy2Attack(SwordEnemy2* owner)
	:SwordEnemy2State(owner)
{
}

void SwordEnemy2Attack::Update(float deltaTime)
{
	if (owner_->GetMesh()->IsEndMotion()) {
		owner_->ChangeState(EnemyState::Idle);
	}
}

void SwordEnemy2Attack::Enter()
{
	owner_->SetAttack(true);
    owner_->LookAtPlayer();
	owner_->ChangeMotion(SwordEnemy2Motion::ChargeATK, false);
}

void SwordEnemy2Attack::Exit()
{
	owner_->SetAttack(false);
    owner_->SetCoolTime();
}

