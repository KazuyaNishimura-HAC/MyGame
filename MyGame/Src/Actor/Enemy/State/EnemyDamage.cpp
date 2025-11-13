#include "EnemyDamage.h"
#include "../../../World/IWorld.h"
#include "../../../GameSystem/InputSystem/InputSystem.h"
EnemyDamage::EnemyDamage(Enemy* owner)
	:EnemyState::EnemyState(owner)
{
}

void EnemyDamage::Update(float deltaTime)
{
	if (owner_->GetMesh()->IsEndMotion()) {
		owner_->ChangeState(Idle);
	}
}

void EnemyDamage::Enter()
{
	owner_->ChangeMotion(Enemy::Hit, false,1,0,0,true);
}

void EnemyDamage::Exit()
{
}

void EnemyDamage::SetID(int id)
{
	stateID = id;
}

int EnemyDamage::GetID()
{
	return stateID;
}
