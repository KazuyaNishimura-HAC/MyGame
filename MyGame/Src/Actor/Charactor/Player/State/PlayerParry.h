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
    void Attack(int count);
    const float waitTime_{ 2.0f };
    bool isParryAttack_{ false };
    std::vector<EffectParam> effectParams{
        {0, { 0,1,1 }, { 0,0,340 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
        {0, { 0,1,1 }, { 0,0,150 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
        {0, { 0,1,1 }, { 0,0,340 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
        {0, { 0,1,1 }, { 0,0,0 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
    };
};

#endif
