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
    float parryTimer_{ 2.0f };
    const float waitTime_{ 2.0f };
    //攻撃待ち中か
    bool isParryWait_{ true };
    //攻撃可能か
    bool isParryAttack_{ false };
    std::vector<EffectParam> effectParams{
        {0, { 0,1,1 }, { 0,0,340 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
        {0, { 0,1,1 }, { 0,0,150 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
        {0, { 0,1,1 }, { 0,0,340 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
        {0, { 0,1,1 }, { 0,0,0 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
    };
};

#endif
