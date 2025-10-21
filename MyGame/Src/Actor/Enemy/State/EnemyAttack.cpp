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
		return;
	}
}

void EnemyAttack::Enter()
{
	owner_->IsAttack(true);
	owner_->ChangeMotion(6, false);
}

void EnemyAttack::Exit()
{
	owner_->IsAttack(false);
}

void EnemyAttack::SetID(int id)
{
	stateID = id;
}

int EnemyAttack::GetID()
{
	return stateID;
}
