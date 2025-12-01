#ifndef PLAYER_GUARD_BREAK_H_
#define PLAYER_GUARD_BREAK_H_
#include "PlayerState.h"

class PlayerGuardBreak : public PlayerState
{
public:
    PlayerGuardBreak(Player* owner);
    void Update(float deltaTime)override;
    void Enter()override;
    void Exit()override;
private:
    const float timer_{ 1.0f };
};

#endif
