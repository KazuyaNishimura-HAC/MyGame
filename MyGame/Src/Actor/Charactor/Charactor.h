#ifndef CHARACTOR_H_
#define CHARACTOR_H_
#include "../Actor.h"
#include "../Model.h"
#include "../../State/StateMachine.h"
#include "../../Graphics/Effect/Effect.h"
#include "AttackCollider.h"

class AttackCollider;
class BattleManager;

struct Status {
    Status(float maxHP, float attack, float defense) :maxHP{ maxHP }, hp{ maxHP }, attack{ attack }, defense{ defense } {};
    //ステータス初期設定
	Status() : Status(100, 10, 0) {};
    float maxHP;
    float hp;
	float attack;
    float defense;
};
class Charactor : public Actor
{
public:
	Charactor(IWorld* world = nullptr, const GSvector3& position = { 0, 0, 0 }, const GSvector3& rotate = { 0, 0, 0 },Status status = {}, GSuint mesh = Model::DefaultCharactor);
	~Charactor()override;
	virtual void Update(float deltaTime)override;
	virtual void LateUpdate(float deltaTime)override;
	virtual void Draw() const override;
    virtual void Init(BattleManager* manager);
    //ダメージを受ける
	void TakeDamage(float damage);
    //攻撃判定を有効化
    virtual void SpawnAttackCollider(float damage = 0.0f, float knockback = 0.0f, float time = 0.01f);
    virtual void OnAttackHit();
    //攻撃を受ける
    virtual void HitAttackCollider(const AttackInfo& atkInfo);
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
    void SetDefense(float defense);
    float GetDefense() const;
	float GetCurrentHealth();
	float GetMaxHealth();
    float GetPrevHealth() const;

	//====================各状態フラグ====================
    void SetVisible(bool visible);
    bool IsVisible() const;
	void SetAttack(bool attack);
	bool IsAttack() const;
	void SetInvincible(bool invincible);
	bool IsInvincible() const;
    void SetHitReactTime();
    void SetHitReactTime(float time);
    bool IsHit() const;
    void SetStun(bool stun);
    bool IsStun() const;
	bool IsDying();

	virtual IWorld* World();
protected:
	StateMachine states_;
    AttackCollider* attackCollider_{ nullptr };
    BattleManager* battleManager_{ nullptr };
    GSuint effectHandle_{ 0 };
private:
    Status status_{};
    //描画するか？
    bool isVisible_{ true };
    //攻撃するか？
    bool isAttack_{ false };
    //無敵か？
    bool isInvincible_{ false };
    //攻撃を食らったか？（isHit有効時間）
    float hitReactTimer_{ 0.0f };
    const float hitReactDuration_{ 0.05f };
    //行動不能か？
    bool isStun_{ false };
    //ダメージを受ける前のHP
    float prevHP_{ 0.0f };
};

#endif
