#ifndef PLAYER_ULTIMATE_SKILL_H_
#define PLAYER_ULTIMATE_SKILL_H_
#include "PlayerState.h"

class UltimateAnimEvent;

class PlayerUltimateSkill : public PlayerState
{
public:
	PlayerUltimateSkill(Player* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
	void SetID(int id = 0)override;
	int GetID()override;
private:
	UltimateAnimEvent* skillEvent_{ nullptr };
};

#endif