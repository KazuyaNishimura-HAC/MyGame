#include "Enemy.h"
#include <imgui/imgui.h>
#include "../../../World/IWorld.h"
#include "../../../GameSystem/InputSystem/InputSystem.h"
#include "../Player/Player.h"
#include "../AttackCollider.h"

#include "EnemyState/EnemyState.h"
#include "EnemyState/EnemyIdle.h"
#include "EnemyState/EnemyMove.h"
Enemy::Enemy(IWorld* world,float groupID, const GSvector3& position, const GSvector3& rotate, Status status, GSuint mesh)
    :Charactor(world,position,rotate,status,mesh)
{
    player_ = world_->GetCharactor("Player");
    tag_ = ActorTag::Enemy;
    colliderOffset_ = { 0.0f,1.0f,0.0f };
    attackCollider_ = new AttackCollider(this,0.75f,{ 0,0,0 },colliderOffset_);
    world_->AddActor(attackCollider_);
    groupID_ = groupID;
}


Enemy::~Enemy()
{
    attackCollider_->Die();
}

void Enemy::Update(float deltaTime)
{
    Charactor::Update(deltaTime);
    if (!CanAttack()) attackCoolTime_ -= deltaTime / 60.0f;
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
    //プレイヤーがいない・もしくは死んでいるならreturn
    if (!player_ || player_->IsDying()) return;
    // ターゲット方向のベクトルを求める
    GSvector3 target = player_->Transform().position() - transform_.position();
    // 前向き方向のベクトルを取得
    GSvector3 forward = transform_.forward();
    // ベクトルのy成分を無効にする
    forward.y = 0.0f;
    target.y = 0.0f;
    // 前向き方向のベクトルとターゲット方向のベクトルの角度差を求める
    float angle = GSvector3::signedAngle(forward, target);
    // ターゲット方向を向く
    transform_.rotate(0.0f, angle * deltaTime, 0.0f);
    // 前進する（ローカル座標基準）
    transform_.translate(0.0f, 0.0f, 0.1f * deltaTime);
}

void Enemy::MoveAttackCollide(float forwardValue)
{
    GSvector3 forward = transform_.forward() * forwardValue;
    //攻撃判定を追従
    attackCollider_->Transform().position(transform_.position() + forward);
}

void Enemy::OnParryHit(const GSvector3& position)
{
    if (IsStun()) return;
    AddBreakPoint(50);
    ChangeState(EnemyState::Parried);
    //固定値て吹っ飛ばす
    Knockback(0.5f,position);
}

void Enemy::SetBattleMode(bool mode)
{
    isBattleMode_ = mode;
}

bool Enemy::IsBattleMode()
{
    return isBattleMode_;
}

void Enemy::AddBreakPoint(float point)
{
    breakPt_ += point;
    if (breakPt_ > maxBreakPt_) breakPt_ = maxBreakPt_;
}

void Enemy::SetBreakPoint(float point)
{
    breakPt_ = CLAMP(point,0,maxBreakPt_);
}

void Enemy::ResetBreakPoint()
{
    breakPt_ = 0.0f;
}

float Enemy::CurrentBreakPoint() const
{
    return breakPt_;
}

void Enemy::SetMaxBreakPoint(float point)
{
    maxBreakPt_ = point;
}

float Enemy::MaxBreakPoint() const
{
    return maxBreakPt_;
}

bool Enemy::IsBroken()
{
    return breakPt_ >= maxBreakPt_;
}

bool Enemy::CanAttack()
{
    return attackCoolTime_ <= 0.0f;
}

void Enemy::SetCoolTime(float time)
{
    attackCoolTime_ = time;
}

void Enemy::LookAtPlayer()
{
    transform_.lookAt(player_->Transform().position());
}

Charactor* Enemy::GetPlayer() const
{
    return player_;
}
