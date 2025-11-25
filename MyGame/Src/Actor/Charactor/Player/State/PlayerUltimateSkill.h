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
private:
    void Attack(int count);
	UltimateAnimEvent* skillEvent_{ nullptr };
    std::vector<EffectParam> effectParams{
        {0, { 0,1,1 }, { 0,0,240 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
        {0, { 0,1,1 }, { 0,0,290 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
        {0, { 0,1.5f,1 }, { 0,0,140 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
    };
};

#endif
