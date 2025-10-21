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
    //ステートの追加
    states_.AddState(EnemyState::Idle, new EnemyIdle(this));
    states_.AddState(EnemyState::Move, new EnemyMove(this));
    states_.AddState(EnemyState::Attack, new EnemyAttack(this));
    states_.ChangeState(EnemyState::Idle);
    collider_ = BoundingSphere(1.0f);
    colliderOffset_ = { 0.0f,1.0f,0.0f };
}

Enemy::Enemy(IWorld* world, GSuint mesh, const GSvector3& position)
    :Enemy{ world, mesh }
{
    //初期座標設定
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
    /*if (!IsAttack() && InputSystem::ButtonTrigger(InputSystem::Button::X)) {
        states_.ChangeState(EnemyState::Attack);
    }*/
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
