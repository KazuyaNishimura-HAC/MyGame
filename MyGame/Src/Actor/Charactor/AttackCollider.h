#ifndef ATTACK_COLLIDER_H_
#define ATTACK_COLLIDER_H_
#include "../Actor.h"

class Charactor;

class AttackCollider : public Actor
{
public:
	AttackCollider(Charactor* owner ,float radius = 1.0f,const GSvector3& pos = { 0,0,0 },const GSvector3& offset = { 0,0,0 });
	~AttackCollider();
	void IsAttack(float time = 1.0f,float attack = 0.0f);
	void Update(float deltTime)override;
	void Draw()const override;
	void React(Actor& other)override;
private:
	Charactor* owner_{ nullptr };
	float attack_{ 1.0f };
	//攻撃の持続時間
	float duration_{ 1.0f };
};

#endif
