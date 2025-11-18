#ifndef PLAYER_ATTACK_H_
#define PLAYER_ATTACK_H_
#include "PlayerState.h"

class PlayerAttack : public PlayerState
{
public:
	PlayerAttack(Player* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
private:
	int combo_ = 0;
};

#endif
