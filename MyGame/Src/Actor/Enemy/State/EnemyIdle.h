#ifndef ENEMY_IDLE_H_
#define ENEMY_IDLE_H_
#include "EnemyState.h"

class Player;

class EnemyIdle : public EnemyState
{
public:
	EnemyIdle(Enemy* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
	void SetID(int id = 0)override;
	int GetID()override;
private:
	Player* player_{ nullptr };
};

#endif