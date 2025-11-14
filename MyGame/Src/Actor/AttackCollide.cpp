#include "AttackCollide.h"
#include "../Actor/Charactor.h"

AttackCollide::AttackCollide(Charactor* owner, float radius, const GSvector3& pos, const GSvector3& offset)
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

AttackCollide::~AttackCollide()
{

}

void AttackCollide::IsAttack(float time, float attack)
{
	collider_.Enable(true);
	duration_ = time;
	attack_ = attack;
}

void AttackCollide::Update(float deltaTime)
{
	collider_.Position(transform_.position() + colliderOffset_);
	if (!collider_.Enable()) return;
	duration_ -= deltaTime / 60.0f;
	if(collider_.Enable()) collider_.Enable(false);
	if (duration_ <= 0) collider_.Enable(false);
}

void AttackCollide::Draw() const
{
	//デバック用
	collider_.Draw();
}
void AttackCollide::React(Actor& other)
{
	Charactor* chara = dynamic_cast<Charactor*>(&other);
	// Charactor以外もしくは攻撃主ならreturn
	if (!chara || owner_ == chara || owner_->GetTag() == chara->GetTag()) return;
	chara->TakeDamage(attack_);
    chara->Knockback(1,owner_->Transform().position());
}
