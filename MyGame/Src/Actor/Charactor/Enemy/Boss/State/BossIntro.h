#ifndef BOSS_INTRO_H_
#define BOSS_INTRO_H_
#include "BossState.h"
class BossIntro : public BossState
{
public:
    BossIntro(Boss* owner);
    void Update(float deltaTime)override;
    void Enter()override;
    void Exit()override;
private:
    float waitTimer{ 1.0f };
    bool isAction_{ false };
    int nextMotion_[2] = { BossMotion::Idle,BossMotion::Attack4 };
    int count_{ 0 };
};

#endif
