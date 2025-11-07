#ifndef ENEMY_ATTACK_H_
#define ENEMY_ATTACK_H_
#include "EnemyState.h"

class EnemyAttack : public EnemyState
{
public:
	EnemyAttack(Enemy* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
	void SetID(int id = 0)override;
	int GetID()override;
};

#endif
