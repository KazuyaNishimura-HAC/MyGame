#ifndef ENEMY_STATE_H_
#define ENEMY_STATE_H_

#include "../../../State/IState.h"
#include "../Enemy.h"
class EnemyState :public IState
{
public:
	enum State {
		Idle,
		Move,
		Stan,
		Attack,
	};

	EnemyState(Enemy* owner) : owner_{ owner } {};
	virtual void Update(float deltaTime)override {};
	virtual void Enter()override {};
	virtual void Exit()override {};

protected:
	Enemy* owner_;
};
#endif