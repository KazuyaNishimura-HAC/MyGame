#include "DefaultEnemy.h"
#include <imgui/imgui.h>
#include "../../../World/IWorld.h"
#include "../../../GameSystem/InputSystem/InputSystem.h"

#include "../State/EnemyState.h"
#include "../State/EnemyIdle.h"
#include "../State/EnemyMove.h"
#include "../State/EnemyAttack.h"

DefaultEnemy::DefaultEnemy(IWorld* world, const GSvector3& position, GSuint mesh)
    :Enemy(world, position, mesh)
{
    //初期座標設定
    transform_.position(position);
    //ステートの追加
    states_.AddState(EnemyState::Idle, new EnemyIdle(this));
    states_.AddState(EnemyState::Move, new EnemyMove(this));
    states_.AddState(EnemyState::Attack, new EnemyAttack(this));
    states_.ChangeState(EnemyState::Idle);
    collider_ = BoundingSphere(1.0f);
    colliderOffset_ = { 0.0f,1.0f,0.0f };
}

DefaultEnemy::~DefaultEnemy()
{
}


void DefaultEnemy::Update(float deltaTime)
{
    Enemy::Update(deltaTime);
}

void DefaultEnemy::LateUpdate(float deltaTime)
{
    Enemy::LateUpdate(deltaTime);

}

void DefaultEnemy::Draw() const
{
    Enemy::Draw();
}

void DefaultEnemy::React(Actor& other)
{
}


void DefaultEnemy::Debug(float deltaTime)
{
}
