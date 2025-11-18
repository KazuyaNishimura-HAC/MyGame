#ifndef PLAYER_DEAD_H_
#define PLAYER_DEAD_H_
#include "PlayerState.h"

class PlayerDead : public PlayerState
{
public:
	PlayerDead(Player* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
private:
};

#endif
