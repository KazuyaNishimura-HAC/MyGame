#ifndef PLAYER_ATTACK_H_
#define PLAYER_ATTACK_H_
#include "PlayerState.h"
class PlayerAttack : public PlayerState
{
public:
	PlayerAttack(Player* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
private:
    void ComboAttack();
    int attackCount_ = 0;
    int combo_ = 0;
    //エフェクトパラメーター
    std::vector<EffectParam> effectParams{
        {Effect::Slash, { 0,1,1 }, { 0,0,135 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
        {Effect::Slash, { 0,1,1 }, { 0,0,0 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
        {Effect::Slash, { 0,1,1 }, { 0,0,225 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
        {Effect::Slash, { 0,1,1 }, { 0,0,315 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
        {Effect::Slash, { 0,1,1 }, { 0,0,0 }, { 1,1,1 }, { 1,0,0,1 },1.5f},
    };
    //コンボに応じた攻撃倍率
    std::vector<float> comboMultiplier_{ 1.0f,1.2f,1.5f,2.0f };
};

#endif
