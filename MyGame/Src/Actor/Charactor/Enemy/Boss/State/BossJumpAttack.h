#ifndef BOSS_JUMP_ATTACK_H_
#define BOSS_JUMP_ATTACK_H_
#include "BossState.h"

class BossJumpAttack : public BossState
{
public:
    BossJumpAttack(Boss* owner);
    void Update(float deltaTime)override;
    void Enter()override;
    void Exit()override;
private:
    void Attack();
    EffectParam currentEffect_{};
    GSuint effectHandle_;
    int motionIndex_{ 0 };
    float waitTimer_{ 0.0f };
    const float waitduration{ 3.0f };
    bool isWait_{ false };
};

#endif
