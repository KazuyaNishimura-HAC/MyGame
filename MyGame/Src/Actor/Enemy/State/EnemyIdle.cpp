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
	if (player_->IsDying()) return;
	float dist = GSvector3::distance(owner_->Transform().position(), player_->Transform().position());
	motionCoolTime_ -= deltaTime / 60.0f;
	if (dist < 5 && motionCoolTime_ <= 0) {
		owner_->ChangeState(State::Move);
	}
}

void EnemyIdle::Enter()
{
	owner_->ChangeMotion(Enemy::Idle, true);
	motionCoolTime_ = owner_->GetCoolTime();
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
