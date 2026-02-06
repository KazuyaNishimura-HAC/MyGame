#ifndef BOSS_ATTACK_H_
#define BOSS_ATTACK_H_
#include "BossState.h"

class BossAttack : public BossState
{
public:
	BossAttack(Boss* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
private:
    void Attack();
    EffectParam currentEffectParam_{};
    GSuint effectHandle_;
    //ランダムモーション
    std::vector<int> randomMotion{ BossMotion::Attack1,BossMotion::Attack2 ,BossMotion::Attack3 };
    int motionIndex_{ 0 };
};

#endif
