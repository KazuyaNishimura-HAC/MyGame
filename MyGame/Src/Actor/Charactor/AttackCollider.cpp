#include "AttackCollider.h"
#include "Charactor.h"

AttackCollider::AttackCollider(Charactor* owner, float radius, const GSvector3& pos, const GSvector3& offset)
{
	owner_ = owner;
    //判定生成者と攻撃主は同じ
    attackInfo_.attacker = owner;
	tag_ = ActorTag::ATKCollider;
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

void AttackCollider::SetAttack(float time, float attack)
{
	collider_.Enable(true);
	duration_ = time;
	attackInfo_.damage = attack;
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
	collider_.Draw();
}
void AttackCollider::React(Actor& other)
{
	Charactor* chara = dynamic_cast<Charactor*>(&other);
	// Charactor以外もしくは攻撃主ならreturn
	if (!chara || owner_ == chara || owner_->GetTag() == chara->GetTag()) return;
    //攻撃者座標・回転を設定
    attackInfo_.hitPos = owner_->Transform().position();
    attackInfo_.hitRot = owner_->Transform().localEulerAngles();
    chara->HitAttackCollider(attackInfo_);
}
