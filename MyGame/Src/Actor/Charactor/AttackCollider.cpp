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
	collider_.SetEnable(false);
}

AttackCollider::~AttackCollider()
{

}

void AttackCollider::SetAttack(float time, float attack)
{
	collider_.SetEnable(true);
	duration_ = time;
	attackInfo_.damage = attack;
}

void AttackCollider::Update(float deltaTime)
{
	collider_.Position(transform_.position() + colliderOffset_);
	if (!collider_.Enable()) return;
	duration_ -= deltaTime / 60.0f;
	if(collider_.Enable()) collider_.SetEnable(false);
	if (duration_ <= 0) collider_.SetEnable(false);
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
    //攻撃成功通知
    owner_->OnAttackHit();
    //Hit側にも通知
    chara->HitAttackCollider(attackInfo_);
}

void AttackCollider::SetRadius(float radius)
{
    collider_.Radius(radius);
}

float AttackCollider::GetRadius()
{
    return collider_.Radius();
}

void AttackCollider::SetOffset(const GSvector3& offset)
{
    colliderOffset_ = offset;
}

const GSvector3& AttackCollider::GetOffset()
{
    return colliderOffset_;
}
