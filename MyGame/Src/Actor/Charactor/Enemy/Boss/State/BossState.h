#ifndef BOSS_STATE_H_
#define BOSS_STATE_H_

#include "../../EnemyState/EnemyState.h"
#include "../Boss.h"
#include "../BossMotion.h"
class BossState :public EnemyState
{
public:
    BossState(Boss* owner) :EnemyState(owner), owner_{ owner } {};
    virtual void Update(float deltaTime)override {};
    virtual void Enter()override {};
    virtual void Exit()override {};
protected:
    Boss* owner_;
};
#endif
