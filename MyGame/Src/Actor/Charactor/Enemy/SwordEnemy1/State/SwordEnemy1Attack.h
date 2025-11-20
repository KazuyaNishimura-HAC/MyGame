#ifndef SWORD_ENEMY1_ATTACK_H_
#define SWORD_ENEMY1_ATTACK_H_
#include "SwordEnemy1State.h"

class SwordEnemy1Attack : public SwordEnemy1State
{
public:
    SwordEnemy1Attack(SwordEnemy1* owner);
	void Update(float deltaTime)override;
	void Enter()override;
	void Exit()override;
};

#endif
