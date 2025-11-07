#include "EnemyAttack.h"
#include "../../../GameSystem/InputSystem/InputSystem.h"
EnemyAttack::EnemyAttack(Enemy* owner)
	:EnemyState::EnemyState(owner)
{
}

void EnemyAttack::Update(float deltaTime)
{
	if (owner_->GetMesh()->IsEndMotion()) {
		owner_->ChangeState(EnemyState::Idle);
	}
}

void EnemyAttack::Enter()
{
	owner_->SetAttack(true);
	owner_->ChangeMotion(Enemy::Attack, false);
}

void EnemyAttack::Exit()
{
	owner_->SetAttack(false);
}

void EnemyAttack::SetID(int id)
{
	stateID = id;
}

int EnemyAttack::GetID()
{
	return stateID;
}
