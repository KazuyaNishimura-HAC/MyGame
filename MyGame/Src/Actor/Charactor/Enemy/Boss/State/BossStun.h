#ifndef BOSS_STUN_H_
#define BOSS_STUN_H_
#include "BossState.h"

class BossStun : public BossState
{
public:
    BossStun(Boss* owner);
    void Update(float deltaTime)override;
    void Enter()override;
    void Exit()override;
private:
    float stunTimer_{ 0.0f };
    const float stunDuration_{ 5.0f };
    GSuint effectHandle_;
};

#endif
