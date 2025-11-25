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
    void ComboAttack();
    int attackCount_ = 0;
    int combo_ = 0;
    std::vector<EffectParam> effectParams{
        {0, { 0,1,1 }, { 0,0,135 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
        {0, { 0,1,1 }, { 0,0,0 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
        {0, { 0,1,1 }, { 0,0,225 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
        {0, { 0,1,1 }, { 0,0,315 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
        {0, { 0,1,1 }, { 0,0,0 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
    };
};

#endif
