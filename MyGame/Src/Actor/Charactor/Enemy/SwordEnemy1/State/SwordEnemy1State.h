#ifndef SWORD_ENEMY1_STATE_H_
#define SWORD_ENEMY1_STATE_H_

#include "../../EnemyState/EnemyState.h"
#include "../SwordEnemy1.h"
#include "../SwordEnemy1Motion.h"
class SwordEnemy1State : public EnemyState
{
public:
    SwordEnemy1State(SwordEnemy1* owner) :EnemyState(owner), owner_{ owner } {};
    virtual void Update(float deltaTime)override {};
    virtual void Enter()override {};
    virtual void Exit()override {};

protected:
    SwordEnemy1* owner_;
};
#endif
