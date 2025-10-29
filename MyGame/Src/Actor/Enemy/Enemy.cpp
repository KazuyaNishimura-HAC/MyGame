#include "Enemy.h"
#include <imgui/imgui.h>
#include "../../Actor/Model.h"
#include "../../World/IWorld.h"
#include "../../GameSystem/InputSystem/InputSystem.h"

#include "State/EnemyState.h"
#include "State/EnemyIdle.h"
#include "State/EnemyMove.h"
#include "State/EnemyAttack.h"
Enemy::Enemy(IWorld* world, GSuint mesh)
    :Actor(mesh)
{
    world_ = world;
}

Enemy::Enemy(IWorld* world, GSuint mesh, const GSvector3& position)
    :Enemy{ world, mesh }
{
    //èâä˙ç¿ïWê›íË
    transform_.position(position);
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
    Actor::Update(deltaTime);
    states_.Update(deltaTime);
    collider_.Position(transform_.position() + colliderOffset_);
}

void Enemy::LateUpdate(float deltaTime)
{
    Actor::LateUpdate(deltaTime);
}

void Enemy::Draw() const
{
    Actor::Draw();
    collider_.Draw();
}

void Enemy::React(Actor& other)
{
}

void Enemy::ChangeState(int state)
{
    states_.ChangeState(state);
}

int Enemy::CurrentState()
{
	return states_.CurrentState();
}

void Enemy::MovePosition(float deltaTime)
{
}

void Enemy::IsAttack(bool isAttack)
{
	isAttack_ = isAttack;
}

bool Enemy::IsAttack()
{
	return isAttack_;
}

IWorld* Enemy::World()
{
	return world_;
}

void Enemy::Debug(float deltaTime)
{
}
