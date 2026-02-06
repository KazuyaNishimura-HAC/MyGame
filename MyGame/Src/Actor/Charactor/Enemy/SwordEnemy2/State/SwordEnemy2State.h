#ifndef SWORD_ENEMY2_STATE_H_
#define SWORD_ENEMY2_STATE_H_

#include "../../EnemyState/EnemyState.h"
#include "../SwordEnemy2.h"
#include "../SwordEnemy2Motion.h"
class SwordEnemy2State : public EnemyState
{
public:
    enum State {
        Guard = 7
    };
    SwordEnemy2State(SwordEnemy2* owner) :EnemyState(owner), owner_{ owner } {};
    virtual void Update(float deltaTime)override {};
    virtual void Enter()override {};
    virtual void Exit()override {};

protected:
    SwordEnemy2* owner_;
};
#endif
