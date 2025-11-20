#ifndef PLAYER_PARRY_H_
#define PLAYER_PARRY_H_
#include "PlayerState.h"

class PlayerParry : public PlayerState
{
public:
    PlayerParry(Player* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
private:
    const float waitTime_{ 2.0f };
    bool isParryAttack_{ false };
};

#endif
