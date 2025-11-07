#ifndef ENEMY_DAMAGE_H_
#define ENEMY_DAMAGE_H_
#include "EnemyState.h"

class EnemyDamage : public EnemyState
{
public:
	EnemyDamage(Enemy* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
	void SetID(int id = 0)override;
	int GetID()override;
private:
};

#endif
