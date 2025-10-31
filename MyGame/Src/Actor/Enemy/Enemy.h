#ifndef ENEMY_H_
#define ENEMY_H_

#include <vector>
#include <GStransform.h>
#include "../Charactor.h"
#include "../Model.h"
#include "../../State/StateMachine.h"

class GUI;

class Enemy : public Charactor
{
public:
    //�R���X�g���N�^
    Enemy(IWorld* world = nullptr, const GSvector3& position = {0, 0, 0}, GSuint mesh = Model::Enemy);
    //�f�X�g���N�^
    ~Enemy()override;

    //�X�V
    virtual void Update(float deltaTime)override;
    virtual void LateUpdate(float deltaTime)override;
    //�`��
    virtual void Draw()const override;
    //�ڐG����
    virtual void React(Actor& other)override;

    virtual void MovePosition(float deltaTime);
    virtual void Debug(float deltaTime)override;
protected:

    bool isAttack_{ false };
};
#endif
