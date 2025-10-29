#include "EnemyIdle.h"
#include "../../../World/IWorld.h"
#include "../../Player/Player.h"
#include "../../../GameSystem/InputSystem/InputSystem.h"
EnemyIdle::EnemyIdle(Enemy* owner)
	:EnemyState::EnemyState(owner)
{
	player_ = owner_->World()->GetPlayer();
}

void EnemyIdle::Update(float deltaTime)
{

	float dist = GSvector3::distance(owner_->Transform().position(), player_->Transform().position());
	if (dist < 5) {
		owner_->ChangeState(State::Move);
	}
}

void EnemyIdle::Enter()
{
	owner_->ChangeMotion(0, true);
}

void EnemyIdle::Exit()
{
}

void EnemyIdle::SetID(int id)
{
	stateID = id;
}

int EnemyIdle::GetID()
{
	return stateID;
}
