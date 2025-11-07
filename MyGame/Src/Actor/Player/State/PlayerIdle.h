#ifndef PLAYER_IDLE_H_
#define PLAYER_IDLE_H_
#include "PlayerState.h"

class PlayerIdle : public PlayerState
{
public:
	PlayerIdle(Player* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
	void SetID(int id = 0)override;
	int GetID()override;
};

#endif
