#ifndef SWORD_ENEMY1_H_
#define SWORD_ENEMY1_H_

#include <vector>
#include <GStransform.h>
#include "../Enemy.h"

class GUI;

class SwordEnemy1 : public Enemy
{
public:
    //コンストラクタ
    SwordEnemy1(IWorld* world = nullptr, const GSvector3& position = {0, 0, 0}, const GSvector3& rotate = { 0, 0, 0 }, Status status = {}, GSuint mesh = Model::Enemy);
    //デストラクタ
    ~SwordEnemy1()override;

    //更新
    void Update(float deltaTime)override;
    void LateUpdate(float deltaTime)override;
    //描画
    void Draw()const override;
    void React(Actor& other)override;
    void TakeDamage(float damage, const GSvector3& attackPos = { 0,0,0 })override;
    virtual void Debug(float deltaTime)override;
private:
    void TestAttack();
};
#endif
