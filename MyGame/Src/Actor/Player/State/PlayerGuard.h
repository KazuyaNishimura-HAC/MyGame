#ifndef PLAYER_GUARD_H_
#define PLAYER_GUARD_H_
#include "PlayerState.h"

class PlayerGuard : public PlayerState
{
public:
    PlayerGuard(Player* owner);
    void Update(float deltaTime)override;
    void Enter()override;
    void Exit()override;
    void SetID(int id = 0)override;
    int GetID()override;
private:
    //パリィ可能時間
    const float parryDuration_{ 0.25f };
    //経過時間
    float parryTimer_{ 0.0f };
};

#endif
