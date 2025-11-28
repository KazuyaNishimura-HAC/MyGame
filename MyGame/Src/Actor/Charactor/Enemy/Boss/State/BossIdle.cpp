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

	if (owner_->IsBattleMode())owner_->ChangeState(State::Move);
}

void BossIdle::Enter()
{
	owner_->ChangeMotion(BossMotion::Idle, true);
}

void BossIdle::Exit()
{
}
