#ifndef ENEMY_DEAD_H_
#define ENEMY_DEAD_H_
#include "EnemyState.h"

class EnemyDead : public EnemyState
{
public:
	EnemyDead(Enemy* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
private:
};

#endif
