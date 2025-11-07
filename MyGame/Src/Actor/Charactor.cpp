#include "Charactor.h"

Charactor::Charactor(IWorld* world, const GSvector3& position,Status status, GSuint mesh)
	:Actor(mesh)
{
	world_ = world;
	//初期座標設定
	transform_.position(position);
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
}

void Charactor::AddDamage(float damage)
{
}

void Charactor::ChangeState(int state)
{
	states_.ChangeState(state);
}

int Charactor::CurrentState()
{
	return states_.CurrentState();
}

void Charactor::SetStatus(Status status)
{
	status_ = status;
}

const Status& Charactor::GetStatus()
{
	return status_;
}

void Charactor::SetAttack(float attack)
{
	status_.atk = attack;
}

float Charactor::GetAttack()
{
	return status_.atk;
}

int Charactor::GetHealth()
{
	return status_.hp;
}

int Charactor::GetMaxHealth()
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
	return status_.hp <= 0;
}

IWorld* Charactor::World()
{
	return world_;
}
