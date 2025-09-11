#include "EnemyIdle.h"
#include "../../../World/IWorld.h"
#include "../../Player/Player.h"
#include "../../../GameSystem/InputSystem/InputSystem.h"
EnemyIdle::EnemyIdle(Enemy* owner)
	:EnemyState::EnemyState(owner)
{
}

void EnemyIdle::Update(float deltaTime)
{
	Player* player_ = owner_->World()->GetPlayer();
}

void EnemyIdle::Enter()
{
	owner_->IsAttack(true);
	owner_->ChangeMotion(0, true);
}

void EnemyIdle::Exit()
{
	owner_->IsAttack(false);
}

void EnemyIdle::SetID(int id)
{
	stateID = id;
}

int EnemyIdle::GetID()
{
	return stateID;
}
