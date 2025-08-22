#ifndef PLAYER_MOVE_H_
#define PLAYER_MOVE_H_
#include "PlayerState.h"

class PlayerMove : public PlayerState
{
public:
	PlayerMove(Player* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
	void SetID(int id = 0)override;
	int GetID()override;
};

#endif