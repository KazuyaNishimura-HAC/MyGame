#include "Charactor.h"
#include <math.h>

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
    //ヒットしていたら経過時間を進める
    if (IsHit()) {
        hitReactTimer_ -= deltaTime / 60.0f;
        //0以下にならないようにクランプ
        hitReactTimer_ = std::max(0.0f, hitReactTimer_);
    }
}

void Charactor::LateUpdate(float deltaTime)
{
	Actor::LateUpdate(deltaTime);
}

void Charactor::Draw() const
{
    if (!isVisible_) return;
	Actor::Draw();
}

void Charactor::Init(BattleManager* manager)
{
    if (battleManager_ != nullptr) return;
    battleManager_ = manager;
}

void Charactor::TakeDamage(float damage)
{
	status_.hp -= damage;
    //0以下にならないようクランプ
    if (status_.hp < 0.0f) status_.hp = CLAMP(status_.hp,0,status_.maxHP);
}

void Charactor::SpawnAttackCollider(float damage, float knockback, float time)
{
    if (!attackCollider_) return;
    attackCollider_->SetAttackInfo(damage,knockback,time);
}

void Charactor::OnAttackHit()
{
}

void Charactor::HitAttackCollider(const AttackInfo& atkInfo)
{
    if (isInvincible_ || IsDying())return;
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
	status_.attack = attack;
}

float Charactor::GetAttackPower()
{
	return status_.attack;
}

void Charactor::SetDefense(float defense)
{
    status_.defense = defense;
}

float Charactor::GetDefense() const
{
    return status_.defense;
}

float Charactor::GetCurrentHealth()
{
	return status_.hp;
}

float Charactor::GetMaxHealth()
{
	return status_.maxHP;
}
void Charactor::SetVisible(bool visible)
{
    isVisible_ = visible;
}
bool Charactor::IsVisible() const
{
    return isVisible_;
}
void Charactor::SetAttack(bool attack)
{
	isAttack_ = attack;
}
bool Charactor::IsAttack() const
{
	return isAttack_;
}

void Charactor::SetInvincible(bool invincible)
{
    isInvincible_ = invincible;
}

bool Charactor::IsInvincible() const
{
	return isInvincible_;
}

void Charactor::SetHitReactTime()
{
    hitReactTimer_ = hitReactDuration_;
}

void Charactor::SetHitReactTime(float time)
{
    hitReactTimer_ = std::max(hitReactDuration_, time);
}

bool Charactor::IsHit() const
{
    return hitReactTimer_ > 0.0f;
}

void Charactor::SetStun(bool stun)
{
    isStun_ = stun;
}

bool Charactor::IsStun() const
{
    return isStun_;
}

bool Charactor::IsDying()
{
	return status_.hp <= 0.0f;
}

IWorld* Charactor::World()
{
	return world_;
}
