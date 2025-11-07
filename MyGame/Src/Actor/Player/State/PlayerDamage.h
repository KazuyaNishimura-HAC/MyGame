#ifndef PLAYER_DAMAGE_H_
#define PLAYER_DAMAGE_H_
#include "PlayerState.h"

class PlayerDamage : public PlayerState
{
public:
	PlayerDamage(Player* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
	void SetID(int id = 0)override;
	int GetID()override;
private:
};

#endif