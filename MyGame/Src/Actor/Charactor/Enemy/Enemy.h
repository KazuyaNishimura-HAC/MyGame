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
    virtual void SetBattleMode(bool mode);
    virtual bool IsBattleMode();
    
    void LookAtPlayer();
protected:
    //ターゲットとなるアクター(Player)を持っておく
    Charactor* player_{ nullptr };
    int groupID_{ 0 };
    EnemyUI* ui_{ nullptr };
    bool isBattleMode_{ false };
};
#endif
