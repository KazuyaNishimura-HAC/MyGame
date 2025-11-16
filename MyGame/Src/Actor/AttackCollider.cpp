#include "AttackCollider.h"
#include "../Actor/Charactor.h"

AttackCollider::AttackCollider(Charactor* owner, float radius, const GSvector3& pos, const GSvector3& offset)
{
	owner_ = owner;
	tag_ = ActorTag::ATKCollide;
	//攻撃主の名前を登録
	name_ = owner_->GetTag() + tag_;
	collider_ = BoundingSphere(radius,pos);
	
	colliderOffset_ = offset;
	collider_.Trigger(true);
	collider_.Enable(false);
}

AttackCollider::~AttackCollider()
{

}

void AttackCollider::IsAttack(float time, float attack)
{
	collider_.Enable(true);
	duration_ = time;
	attack_ = attack;
}

void AttackCollider::Update(float deltaTime)
{
	collider_.Position(transform_.position() + colliderOffset_);
	if (!collider_.Enable()) return;
	duration_ -= deltaTime / 60.0f;
	if(collider_.Enable()) collider_.Enable(false);
	if (duration_ <= 0) collider_.Enable(false);
}

void AttackCollider::Draw() const
{
	//デバック用
	//collider_.Draw();
}
void AttackCollider::React(Actor& other)
{
	Charactor* chara = dynamic_cast<Charactor*>(&other);
	// Charactor以外もしくは攻撃主ならreturn
	if (!chara || owner_ == chara || owner_->GetTag() == chara->GetTag()) return;
	chara->TakeDamage(attack_, owner_->Transform().position());
}
