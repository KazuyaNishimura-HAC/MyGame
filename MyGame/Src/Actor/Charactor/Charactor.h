#ifndef CHARACTOR_H_
#define CHARACTOR_H_
#include "../Actor.h"
#include "../Model.h"
#include "../../State/StateMachine.h"
#include "../../Graphics/Effect/Effect.h"

class AttackCollider;

struct Status {
    Status(float maxHP, float atk) :maxHP{ maxHP }, hp{ maxHP }, atk{ atk } {};
    //ステータス初期設定
	Status() : Status(60, 10) {};
    float maxHP;
    float hp;
	float atk;
};
class Charactor : public Actor
{
public:
	Charactor(IWorld* world = nullptr, const GSvector3& position = { 0, 0, 0 }, const GSvector3& rotate = { 0, 0, 0 },Status status = {}, GSuint mesh = Model::DefaultCharactor);
	~Charactor()override;
	virtual void Update(float deltaTime)override;
	virtual void LateUpdate(float deltaTime)override;
	virtual void Draw() const override;
    //ダメージを受ける
	virtual void TakeDamage(float damage,const GSvector3& attackPos = { 0,0,0 });
    //攻撃判定を有効化
    virtual void SpawnAttackCollider(float time,float atk);
    //ノックバック
    virtual void Knockback(float power = 1.0f, const GSvector3& position = { 0,0,0 });
	//ステート設定・取得
	void ChangeState(int state);
	int CurrentState();
    bool IsCurrentState(int state);
	//====================各ステータス====================
	void SetStatus(Status status);
	const Status& GetStatus();
	void SetAttackPower(float attack);
	float GetAttackPower();
	float GetCurrentHealth();
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
    AttackCollider* attackCollider_{ nullptr };
    std::unordered_map <Effect::ID, GSuint> effectHandles_;
	Status status_{};
	bool isAttack_{ false };
	bool invincible_{ false };
};

#endif
