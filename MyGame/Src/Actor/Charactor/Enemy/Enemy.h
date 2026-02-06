#ifndef ENEMY_H_
#define ENEMY_H_

#include <vector>
#include <GStransform.h>
#include "../Charactor.h"
class GUI;
class EnemyUI;

class Enemy : public Charactor
{
public:
    //コンストラクタ
    Enemy(IWorld* world = nullptr,float groupID = 0, const GSvector3& position = {0, 0, 0}, const GSvector3& rotate = { 0, 0, 0 }, Status status = {}, GSuint mesh = Model::Enemy);
    //デストラクタ
    ~Enemy()override;

    //更新
    virtual void Update(float deltaTime)override;
    virtual void LateUpdate(float deltaTime)override;
    //描画
    virtual void Draw()const override;
    //接触判定
    virtual void React(Actor& other)override;

    virtual void MovePosition(float deltaTime);
    virtual void MoveAttackCollide(float forwardValue = 1.0f);
    virtual void OnParryHit(const GSvector3& position);
    //戦闘モードに移行するか
    void SetBattleMode(bool mode);
    bool IsBattleMode();
    //ブレイク値設定
    void AddBreakPoint(float point);
    void SetBreakPoint(float point);
    void ResetBreakPoint();
    float CurrentBreakPoint() const;
    //最大ブレイク値設定
    void SetMaxBreakPoint(float point);
    float MaxBreakPoint() const;
    //ブレイク可能か
    bool IsBroken();
    //攻撃可能か
    bool CanAttack();
    void SetCoolTime(float time = 1.5f);
    //プレイヤ方向を向く
    void LookAtPlayer();
    Charactor* GetPlayer()const;
protected:
    //ターゲットとなるアクター(Player)を持っておく
    Charactor* player_{ nullptr };
    //どのフィールドグループに属しているか
    int groupID_{ 0 };
    EnemyUI* ui_{ nullptr };
    bool isBattleMode_{ false };
    float breakPt_{ 0 };
    float maxBreakPt_{ 100.0f };

    float attackCoolTime_{ 1.5f };
};
#endif
