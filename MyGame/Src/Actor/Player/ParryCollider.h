#ifndef PARRY_COLLIDER_H_
#define PARRY_COLLIDER_H_
#include "../../Actor/Actor.h"

class Charactor;

class ParryCollider : public Actor
{
public:
    ParryCollider(Charactor* owner,float radius = 1.0f, const GSvector3& pos = { 0,0,0 }, const GSvector3& offset = { 0,0,0 });
    ~ParryCollider();
    void IsParry(float time = 1.0f);
    void Update(float deltTime)override;
    void Draw()const override;
    void React(Actor& other)override;
private:
    Charactor* owner_{ nullptr };
    //攻撃の持続時間
    float duration_{ 1.0f };
};

#endif
