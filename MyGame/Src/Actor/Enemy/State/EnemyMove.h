#ifndef ENEMY_MOVE_H_
#define ENEMY_MOVE_H_
#include "EnemyState.h"

class EnemyMove : public EnemyState
{
public:
	EnemyMove(Enemy* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
	void SetID(int id = 0)override;
	int GetID()override;
};

#endif