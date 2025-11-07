#include "EnemyDead.h"
#include "../../../World/IWorld.h"
#include "../../../GameSystem/InputSystem/InputSystem.h"
EnemyDead::EnemyDead(Enemy* owner)
	:EnemyState::EnemyState(owner)
{
}

void EnemyDead::Update(float deltaTime)
{
	if (!owner_->GetMesh()->IsEndMotion()) return;
	owner_->Die();
}

void EnemyDead::Enter()
{
	owner_->ChangeMotion(Enemy::Death,false);
	//“–‚½‚è”»’è‚ð–³Œø‰»
	owner_->SetEnable(false);
}

void EnemyDead::Exit()
{
}

void EnemyDead::SetID(int id)
{
	stateID = id;
}

int EnemyDead::GetID()
{
	return stateID;
}
