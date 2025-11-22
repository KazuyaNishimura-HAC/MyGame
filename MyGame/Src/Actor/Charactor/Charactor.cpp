#include "Charactor.h"

Charactor::Charactor(IWorld* world, const GSvector3& position, const GSvector3& rotate,Status status, GSuint mesh)
	:Actor(mesh)
{
	world_ = world;
	//初期座標設定
	transform_.position(position);
    transform_.rotate(rotate);
	status_ = status;
}

Charactor::~Charactor()
{
}

void Charactor::Update(float deltaTime)
{
	Actor::Update(deltaTime);
	states_.Update(deltaTime);
	collider_.Position(transform_.position() + colliderOffset_);
}

void Charactor::LateUpdate(float deltaTime)
{
	Actor::LateUpdate(deltaTime);
}

void Charactor::Draw() const
{
	Actor::Draw();
}

void Charactor::TakeDamage(float damage)
{
	status_.hp -= damage;
    //0以下にならないようクランプ
    if (status_.hp < 0.0f) status_.hp = CLAMP(status_.hp,0,status_.maxHP);
}

void Charactor::SpawnAttackCollider(float time, float atk)
{
    if (!attackCollider_) return;
    attackCollider_->SetAttack(time,atk);
}

void Charactor::HitAttackCollider(const AttackInfo& atkInfo)
{
    if (invincible_ || IsDying())return;
    TakeDamage(atkInfo.damage);
}

void Charactor::Knockback(float power, const GSvector3& position)
{
    GSvector3 dir = transform_.position() - position;
    dir.normalized();
    dir *= power;
    transform_.position(transform_.position() + dir);
}

void Charactor::ChangeState(int state)
{
	states_.ChangeState(state);
}

int Charactor::CurrentState()
{
	return states_.CurrentState();
}

bool Charactor::IsCurrentState(int state)
{
    return states_.IsCurrentState(state);
}

void Charactor::SetStatus(Status status)
{
	status_ = status;
}

const Status& Charactor::GetStatus()
{
	return status_;
}

void Charactor::SetAttackPower(float attack)
{
	status_.atk = attack;
}

float Charactor::GetAttackPower()
{
	return status_.atk;
}

float Charactor::GetCurrentHealth()
{
	return status_.hp;
}

float Charactor::GetMaxHealth()
{
	return status_.maxHP;
}
void Charactor::SetAttack(bool isAttack)
{
	isAttack_ = isAttack;
}
bool Charactor::IsAttack()
{
	return isAttack_;
}

void Charactor::SetInvincible(bool isInvincible)
{
	invincible_ = isInvincible;
}

bool Charactor::IsInvincible()
{
	return invincible_;
}

bool Charactor::IsDying()
{
	return status_.hp <= 0.0f;
}

IWorld* Charactor::World()
{
	return world_;
}
