#include "PlayerIdle.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
#include "../../../../World/IWorld.h"
PlayerIdle::PlayerIdle(Player* owner)
	:PlayerState::PlayerState(owner)
{
}

void PlayerIdle::Update(float deltaTime)
{
    if (owner_->World()->IsRunningEvent()) return;

	if (InputSystem::LeftStick() != GSvector2::zero()) owner_->ChangeState(PlayerState::Move);
}

void PlayerIdle::Enter()
{
	owner_->ChangeMotion(PlayerMotion::Idle,true);
}

void PlayerIdle::Exit()
{

}
