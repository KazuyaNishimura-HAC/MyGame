#include "EnemyMove.h"
#include "../../../GameSystem/InputSystem/InputSystem.h"
EnemyMove::EnemyMove(Enemy* owner)
	:EnemyState::EnemyState(owner)
{
}

void EnemyMove::Update(float deltaTime)
{
	owner_->Transform().position();
}

void EnemyMove::Enter()
{
	owner_->IsAttack(true);
	owner_->ChangeMotion(1);
}

void EnemyMove::Exit()
{
	owner_->IsAttack(false);
}

void EnemyMove::SetID(int id)
{
	stateID = id;
}

int EnemyMove::GetID()
{
	return stateID;
}
