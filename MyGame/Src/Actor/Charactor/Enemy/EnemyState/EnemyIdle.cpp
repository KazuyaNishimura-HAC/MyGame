#include "EnemyIdle.h"
#include "../../Player/Player.h"
#include "../../../../World/IWorld.h"
#include "../../../../GameSystem/InputSystem/InputSystem.h"
EnemyIdle::EnemyIdle(Enemy* owner)
	:EnemyState::EnemyState(owner)
{
	player_ = owner_->World()->GetPlayer();
}

void EnemyIdle::Update(float deltaTime)
{
	if (player_->IsDying()) return;
	float dist = GSvector3::distance(owner_->Transform().position(), player_->Transform().position());
	if (dist < 10) {
        //戦闘モードに切替
        owner_->SetBattleMode(true);
		owner_->ChangeState(State::Move);
	}
}

void EnemyIdle::Enter()
{
	owner_->ChangeMotion(BasicEnemyMotion::Idle);
}

void EnemyIdle::Exit()
{
}
