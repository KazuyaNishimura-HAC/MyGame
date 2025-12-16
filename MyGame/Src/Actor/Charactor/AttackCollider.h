#ifndef ATTACK_COLLIDER_H_
#define ATTACK_COLLIDER_H_
#include "../Actor.h"

class Charactor;

struct AttackInfo {
    float damage{ 1.0f };
    float knockbackPower{ 1.0f };
    GSvector3 hitPos{};
    GSvector3 hitRot{};
    Charactor* attacker{ nullptr };
};
class AttackCollider : public Actor
{
public:
	AttackCollider(Charactor* owner ,float radius = 1.0f,const GSvector3& pos = { 0,0,0 },const GSvector3& offset = { 0,0,0 });
	~AttackCollider();
	void SetAttackInfo(float time = 1.0f,float damage = 0.0f);
	void Update(float deltTime)override;
	void Draw()const override;
	void React(Actor& other)override;
    void SetRadius(float radius);
    float GetRadius();
    void SetOffset(const GSvector3& offset);
    const GSvector3& GetOffset();
private:
    //生成主
	Charactor* owner_{ nullptr };
    //攻撃情報
    AttackInfo attackInfo_{};
	//攻撃の持続時間
	float duration_{ 1.0f };
};

#endif
