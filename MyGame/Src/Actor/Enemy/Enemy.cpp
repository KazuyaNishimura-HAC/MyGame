#include "Enemy.h"
#include <imgui/imgui.h>
#include "../../World/IWorld.h"
#include "../../GameSystem/InputSystem/InputSystem.h"

#include "State/EnemyState.h"
#include "State/EnemyIdle.h"
#include "State/EnemyMove.h"
#include "State/EnemyAttack.h"
Enemy::Enemy(IWorld* world, const GSvector3& position, GSuint mesh)
    :Charactor(world,position,mesh)
{
}


Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
    Charactor::Update(deltaTime);
    collider_.Position(transform_.position() + colliderOffset_);
}

void Enemy::LateUpdate(float deltaTime)
{
    Charactor::LateUpdate(deltaTime);
}

void Enemy::Draw() const
{
    Charactor::Draw();
    
    collider_.Draw();
}

void Enemy::React(Actor& other)
{
}

void Enemy::MovePosition(float deltaTime)
{
}


void Enemy::Debug(float deltaTime)
{
}
