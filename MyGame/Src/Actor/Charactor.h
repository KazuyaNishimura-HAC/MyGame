#ifndef CHARACTOR_H_
#define CHARACTOR_H_
#include "Actor.h"
#include "../Actor/Model.h"
#include "../State/StateMachine.h"
#include "../Actor/AttackCollide.h"
class Charactor : public Actor
{
public:
	Charactor(IWorld* world = nullptr, const GSvector3& position = { 0, 0, 0 }, GSuint mesh = Model::DefaultCharactor);
	~Charactor()override;
	virtual void Update(float deltaTime)override;
	virtual void LateUpdate(float deltaTime)override;
	virtual void Draw() const override;
	virtual void TakeDamage(float damage);
	virtual void AddDamage(float damage);
	void ChangeState(int state);
	int CurrentState();

	void SetAttack(bool isAttack);
	bool IsAttack();

	void SetInvincible(bool isInvincible);
	bool IsInvincible();

	int GetHealth();
	int GetMaxHealth();
	bool IsDying();

	virtual IWorld* World();
protected:
	StateMachine states_;
	AttackCollide* attackCollider_{ nullptr };
	bool isAttack_{ false };
	int hp_;
	int maxHP_{ 60 };
	bool invincible_{ false };
};

#endif