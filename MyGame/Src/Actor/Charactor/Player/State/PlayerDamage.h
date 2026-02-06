#ifndef PLAYER_DAMAGE_H_
#define PLAYER_DAMAGE_H_
#include "PlayerState.h"
#include "../../../../Graphics/Effect/PostEffect.h"

class PlayerDamage : public PlayerState
{
public:
	PlayerDamage(Player* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
private:
    float vignetteIntencity_{ 0.0f };
    const GSvector3 vignetteColor_{ 1.0f,0.0f,0.0f };
    const float effectEndTime_{ 0.5f };
    float timer_{ 0.0f };
    //一度専用フラグ
    bool isExecuted_{ false };
    GSuint effectHandle_;
};

#endif
