#ifndef BOSS_ATTACK_H_
#define BOSS_ATTACK_H_
#include "BossState.h"

class BossAttack : public BossState
{
public:
	BossAttack(Boss* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
};

#endif
