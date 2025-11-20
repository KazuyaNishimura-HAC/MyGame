#include "EnemyMove.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
EnemyMove::EnemyMove(Enemy* owner)
	:EnemyState::EnemyState(owner)
{
}

void EnemyMove::Update(float deltaTime)
{
	owner_->Transform().position();
	owner_->MovePosition(deltaTime);
}

void EnemyMove::Enter()
{
	owner_->ChangeMotion(BasicEnemyMotion::Run);
}

void EnemyMove::Exit()
{
}
