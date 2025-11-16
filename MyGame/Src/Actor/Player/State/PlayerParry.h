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
	void SetID(int id = 0)override;
	int GetID()override;
private:
    const float waitTime_{ 1.0f };
    bool isParryAttack_{ false };
};

#endif
