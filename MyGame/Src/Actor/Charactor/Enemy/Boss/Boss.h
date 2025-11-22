#ifndef BOSS_H_
#define BOSS_H_
#include "../Enemy.h"
class Boss : public Enemy
{
public:
    

    Boss(IWorld* world = nullptr,const GSvector3& position = { 0,0,0 },const GSvector3& rotate = { 0,0,0 },Status status = {}, GSuint mesh = Model::Boss);
    ~Boss()override;

    //更新
    void Update(float deltaTime)override;
    void LateUpdate(float deltaTime)override;
    //描画
    void Draw()const override;
    void React(Actor& other)override;
    void HitAttackCollider(const AttackInfo& atkInfo)override;
    void Debug(float deltaTime)override;
private:
    void Attack();
};

#endif
