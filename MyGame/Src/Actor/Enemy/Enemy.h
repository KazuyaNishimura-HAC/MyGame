#ifndef ENEMY_H_
#define ENEMY_H_

#include <vector>
#include <GStransform.h>
#include "../Charactor.h"
class GUI;

class Enemy : public Charactor
{
public:
    enum Motion {
        Idle,
        Run,
        Attack,
        Combo2,
        Combo3,
        Attack2,
        SkillCoolTime,
        AttackSkill,
        UltSkill,
        Parry,
        Hit,
        Death,
        Death2,
        Death3
    };
    //コンストラクタ
    Enemy(IWorld* world = nullptr, const GSvector3& position = {0, 0, 0}, GSuint mesh = Model::Enemy);
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
    virtual void MoveAttackCollide();
    virtual void SetCoolTime(float time);
    virtual float GetCoolTime();
    virtual void Debug(float deltaTime)override;
protected:
    //ターゲットとなるアクター(Player)を持っておく
    Charactor* player_{ nullptr };
    float damageCoolTime_ = { 0.0f };
};
#endif
