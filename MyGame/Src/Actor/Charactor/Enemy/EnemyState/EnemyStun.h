#ifndef ENEMY_STUN_H_
#define ENEMY_STUN_H_
#include "EnemyState.h"

class EnemyStun : public EnemyState
{
public:
    EnemyStun(Enemy* owner);
    void Update(float deltaTime)override;
    void Enter()override;
    void Exit()override;
private:
    float stunTimer_{ 0.0f };
    const float stunDuration_{ 5.0f };
    GSuint effectHandle_{ 0 };
};

#endif
