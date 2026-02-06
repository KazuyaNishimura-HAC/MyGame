#ifndef SWORD_ENEMY2_ATTACK_H_
#define SWORD_ENEMY2_ATTACK_H_
#include "SwordEnemy2State.h"

class SwordEnemy2Attack : public SwordEnemy2State
{
public:
    SwordEnemy2Attack(SwordEnemy2* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
};

#endif
