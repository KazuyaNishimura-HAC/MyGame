#ifndef ENEMY_PARRIED_H_
#define ENEMY_PARRIED_H_
#include "EnemyState.h"

class EnemyParried : public EnemyState
{
public:
    EnemyParried(Enemy* owner);
    void Update(float deltaTime)override;
    void Enter()override;
    void Exit()override;
private:
};

#endif
