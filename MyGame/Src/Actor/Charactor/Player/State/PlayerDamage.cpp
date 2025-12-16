#include "PlayerDamage.h"

PlayerDamage::PlayerDamage(Player* owner)
	:PlayerState::PlayerState(owner)
{
}

void PlayerDamage::Update(float deltaTime)
{
	if (owner_->GetMesh()->IsEndMotion()) {
		owner_->ChangeState(Idle);
	}
}

void PlayerDamage::Enter()
{
	owner_->ChangeMotion(PlayerMotion::Hit, false,1,0,0,true);
    EffectParam param;
    param.handle = Effect::Hit;
    param.position = owner_->Transform().position() + GSvector3{0,1,0};
    param.scale = { 0.5f,0.5f,0.5f };
    Effect::SetEffectParam(param);
}

void PlayerDamage::Exit()
{
}
