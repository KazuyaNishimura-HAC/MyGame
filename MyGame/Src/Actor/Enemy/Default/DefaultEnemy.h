#ifndef DEFAULT_ENEMY_H_
#define DEFAULT_ENEMY_H_

#include <vector>
#include <GStransform.h>
#include "../../../Actor/Enemy/Enemy.h"

class GUI;

class DefaultEnemy : public Enemy
{
public:
    //コンストラクタ
    DefaultEnemy(IWorld* world = nullptr, const GSvector3& position = {0, 0, 0}, Status status = Status(), GSuint mesh = Model::Enemy);
    //デストラクタ
    ~DefaultEnemy()override;

    //更新
    void Update(float deltaTime)override;
    void LateUpdate(float deltaTime)override;
    //描画
    void Draw()const override;
    void React(Actor& other)override;
    void TakeDamage(float damage)override;
    virtual void Debug(float deltaTime)override;
private:
    void TestAttack();
};
#endif
