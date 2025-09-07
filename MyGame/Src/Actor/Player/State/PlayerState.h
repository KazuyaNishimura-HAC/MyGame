#ifndef PLAYER_STATE_H_
#define PLAYER_STATE_H_

#include "../../../State/IState.h"
#include "../Player.h"
class PlayerState :public IState
{
public:
	enum State {
		Idle,
		Move,
		Stan,
		Attack,
		Skill,
		Ultimate
	};

	PlayerState(Player* owner) : owner_{ owner }{};
	virtual void Update(float deltaTime)override {};
	virtual void Enter()override {};
	virtual void Exit()override {};

protected:
	Player* owner_;
};
#endif