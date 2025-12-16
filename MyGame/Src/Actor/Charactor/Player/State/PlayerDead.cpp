#include "PlayerDead.h"
#include "../../../../World/IWorld.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
PlayerDead::PlayerDead(Player* owner)
	:PlayerState::PlayerState(owner)
{
}

void PlayerDead::Update(float deltaTime)
{
	if (!owner_->GetMesh()->IsEndMotion()) return;
	owner_->Die();
}

void PlayerDead::Enter()
{
	owner_->ChangeMotion(PlayerMotion::Die, false);
	//当たり判定を無効化
	owner_->SetEnable(false);
}

void PlayerDead::Exit()
{
}
