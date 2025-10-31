#include "Charactor.h"

Charactor::Charactor(IWorld* world, const GSvector3& position, GSuint mesh)
	:Actor(mesh)
{
	world_ = world;
	//èâä˙ç¿ïWê›íË
	transform_.position(position);
}

Charactor::~Charactor()
{
}

void Charactor::Update(float deltaTime)
{
	Actor::Update(deltaTime);
	states_.Update(deltaTime);
}

void Charactor::LateUpdate(float deltaTime)
{
	Actor::LateUpdate(deltaTime);
}

void Charactor::Draw() const
{
	Actor::Draw();
}

void Charactor::TakeDamage()
{
}

void Charactor::AddDamage()
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

void Charactor::IsAttack(bool isAttack)
{
	isAttack_ = isAttack;
}

bool Charactor::IsAttack()
{
	return isAttack_;
}

IWorld* Charactor::World()
{
	return world_;
}
