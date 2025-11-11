#ifndef CHARACTOR_H_
#define CHARACTOR_H_
#include "Actor.h"
#include "../Actor/Model.h"
#include "../State/StateMachine.h"

class AttackCollide;

struct Status {
	Status(float hp, float atk) :hp{ hp }, atk{ atk } { maxHP = hp; };
    //ステータス初期設定
	Status() : Status(60, 10) {};
    float hp;
    float maxHP;
	float atk;
};
class Charactor : public Actor
{
public:
	Charactor(IWorld* world = nullptr, const GSvector3& position = { 0, 0, 0 },Status status = Status(), GSuint mesh = Model::DefaultCharactor);
	~Charactor()override;
	virtual void Update(float deltaTime)override;
	virtual void LateUpdate(float deltaTime)override;
	virtual void Draw() const override;
	virtual void TakeDamage(float damage);
	virtual void AddDamage(float damage);
	//ステート設定・取得
	void ChangeState(int state);
	int CurrentState();
	//====================各ステータス====================
	void SetStatus(Status status);
	const Status& GetStatus();
	void SetAttack(float attack);
	float GetAttack();
	float GetHealth();
	float GetMaxHealth();

	//====================各状態フラグ====================
	void SetAttack(bool isAttack);
	bool IsAttack();
	void SetInvincible(bool isInvincible);
	bool IsInvincible();
	bool IsDying();

	virtual IWorld* World();
protected:
	StateMachine states_;
	AttackCollide* attackCollider_{ nullptr };
	Status status_{};
	bool isAttack_{ false };
	bool invincible_{ false };
};

#endif
