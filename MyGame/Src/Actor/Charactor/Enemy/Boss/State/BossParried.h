#ifndef BOSS_PARRIED_H_
#define BOSS_PARRIED_H_
#include "BossState.h"

class BossParried : public BossState
{
public:
    BossParried(Boss* owner);
    void Update(float deltaTime)override;
    void Enter()override;
    void Exit()override;
private:
};

#endif
