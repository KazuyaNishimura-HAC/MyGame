#ifndef CHARACTOR_H_
#define CHARACTOR_H_
#include "Actor.h"
#include "../Actor/Model.h"
#include "../State/StateMachine.h"
class Charactor : public Actor
{
public:
	Charactor(IWorld* world = nullptr, const GSvector3& position = { 0, 0, 0 }, GSuint mesh = Model::DefaultCharactor);
	~Charactor()override;
	virtual void Update(float deltaTime)override;
	virtual void LateUpdate(float deltaTime)override;
	virtual void Draw() const override;
	virtual void TakeDamage();
	virtual void AddDamage();
	void ChangeState(int state);
	int CurrentState();

	void IsAttack(bool isAttack);
	bool IsAttack();

	virtual IWorld* World();
protected:
	StateMachine states_;
	bool isAttack_{ false };
};

#endif