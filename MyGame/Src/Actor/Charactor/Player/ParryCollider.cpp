#include "ParryCollider.h"
#include "../Charactor.h"
#include "../Enemy/Enemy.h"

ParryCollider::ParryCollider(Charactor* owner, float radius, const GSvector3& pos, const GSvector3& offset)
{
    owner_ = owner;
    tag_ = ActorTag::Collider;
    //攻撃主の名前を登録
    name_ = ActorName::ParryCollider;
    collider_ = BoundingSphere(radius, pos);

    colliderOffset_ = offset;
    collider_.Trigger(true);
    collider_.Enable(false);
}

ParryCollider::~ParryCollider()
{

}

void ParryCollider::IsParry(float time)
{
    collider_.Enable(true);
    duration_ = time;
}

void ParryCollider::Update(float deltaTime)
{
    collider_.Position(transform_.position() + colliderOffset_);
    if (!collider_.Enable()) return;
    duration_ -= deltaTime / 60.0f;
    if (collider_.Enable()) collider_.Enable(false);
    if (duration_ <= 0) collider_.Enable(false);
}

void ParryCollider::Draw() const
{
    //デバック用
    collider_.Draw();
}
void ParryCollider::React(Actor& other)
{
    Enemy* chara = dynamic_cast<Enemy*>(&other);
    // エネミー以外もしくは攻撃主ならreturn
    if (!chara || owner_ == chara) return;
    chara->OnParryHit(owner_->Transform().position());
}
