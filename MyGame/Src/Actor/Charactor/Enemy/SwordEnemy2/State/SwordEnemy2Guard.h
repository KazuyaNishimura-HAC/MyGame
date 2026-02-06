#ifndef SWORD_ENEMY2_GUARD_H_
#define SWORD_ENEMY2_GUARD_H_
#include "SwordEnemy2State.h"

class SwordEnemy2Guard : public SwordEnemy2State
{
public:
    SwordEnemy2Guard(SwordEnemy2* owner);
    void Update(float deltaTime)override;
    void Enter()override;
    void Exit()override;
};

#endif
