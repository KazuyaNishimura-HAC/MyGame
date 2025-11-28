#ifndef BOSS_DEAD_H_
#define BOSS_DEAD_H_
#include "BossState.h"

class BossDead : public BossState
{
public:
	BossDead(Boss* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
private:
};

#endif
