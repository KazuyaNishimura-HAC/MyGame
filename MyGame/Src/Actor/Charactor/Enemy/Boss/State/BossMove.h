#ifndef ENEMY_MOVE_H_
#define ENEMY_MOVE_H_
#include "BossState.h"

class BossMove : public BossState
{
public:
	BossMove(Boss* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
	void SetID(int id = 0)override;
	int GetID()override;
};

#endif
