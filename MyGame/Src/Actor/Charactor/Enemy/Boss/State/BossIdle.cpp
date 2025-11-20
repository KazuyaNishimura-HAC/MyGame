#include "BossIdle.h"
#include "../../../../../World/IWorld.h"
#include "../../../Player/Player.h"
BossIdle::BossIdle(Boss* owner)
	:BossState::BossState(owner)
{
	player_ = owner_->World()->GetPlayer();
}

void BossIdle::Update(float deltaTime)
{
	if (player_->IsDying()) return;
	float dist = GSvector3::distance(owner_->Transform().position(), player_->Transform().position());
	if (dist < 5) {
		owner_->ChangeState(State::Move);
	}
}

void BossIdle::Enter()
{
	owner_->ChangeMotion(BossMotion::Idle, true);
}

void BossIdle::Exit()
{
}

void BossIdle::SetID(int id)
{
	stateID = id;
}

int BossIdle::GetID()
{
	return stateID;
}
