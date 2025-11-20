#ifndef BOSS_IDLE_H_
#define BOSS_IDLE_H_
#include "BossState.h"

class Player;

class BossIdle : public BossState
{
public:
	BossIdle(Boss* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
	void SetID(int id = 0)override;
	int GetID()override;
private:
	Player* player_{ nullptr };
};

#endif
