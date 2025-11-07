#include "Charactor.h"

Charactor::Charactor(IWorld* world, const GSvector3& position, GSuint mesh)
	:Actor(mesh)
{
	world_ = world;
	//èâä˙ç¿ïWê›íË
	transform_.position(position);
	hp_ = maxHP_;
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
	hp_ -= damage;
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

int Charactor::GetHealth()
{
	return hp_;
}

int Charactor::GetMaxHealth()
{
	return maxHP_;
}

bool Charactor::IsDying()
{
	return hp_ <= 0;
}

IWorld* Charactor::World()
{
	return world_;
}
