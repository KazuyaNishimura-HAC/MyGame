#ifndef DEFAULT_ENEMY_H_
#define DEFAULT_ENEMY_H_

#include <vector>
#include <GStransform.h>
#include "../../../Actor/Enemy/Enemy.h"

class GUI;

class DefaultEnemy : public Enemy
{
public:
    //�R���X�g���N�^
    DefaultEnemy(IWorld* world = nullptr, const GSvector3& position = {0, 0, 0}, GSuint mesh = Model::Enemy);
    //�f�X�g���N�^
    ~DefaultEnemy()override;

    //�X�V
    void Update(float deltaTime)override;
    void LateUpdate(float deltaTime)override;
    //�`��
    void Draw()const override;
    //�ڐG����
    void React(Actor& other)override;

    virtual void Debug(float deltaTime)override;
};
#endif
