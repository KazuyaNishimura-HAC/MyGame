#ifndef BOSS_DAMAGE_H_
#define BOSS_DAMAGE_H_
#include "BossState.h"

class BossDamage : public BossState
{
public:
	BossDamage(Boss* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
	void SetID(int id = 0)override;
	int GetID()override;
private:
};

#endif
