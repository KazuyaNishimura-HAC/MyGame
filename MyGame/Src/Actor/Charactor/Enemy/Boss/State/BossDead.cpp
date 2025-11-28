#include "BossDead.h"
BossDead::BossDead(Boss* owner)
	:BossState::BossState(owner)
{
}

void BossDead::Update(float deltaTime)
{
	if (!owner_->GetMesh()->IsEndMotion()) return;
	owner_->Die();
}

void BossDead::Enter()
{
	owner_->ChangeMotion(BossMotion::Die,false);
	//当たり判定を無効化
	owner_->SetEnable(false);
}

void BossDead::Exit()
{
}
