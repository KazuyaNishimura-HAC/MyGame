#ifndef ENEMY_H_
#define ENEMY_H_

#include <vector>
#include <GStransform.h>
#include "../Actor.h"
#include "../Model.h"
#include "../../State/StateMachine.h"

class GUI;

class Enemy : public Actor
{
public:
    //�R���X�g���N�^
    Enemy(IWorld* world = nullptr, GSuint mesh = Model::Enemy);
    Enemy(IWorld* world, GSuint mesh, const GSvector3& position);
    //�f�X�g���N�^
    ~Enemy()override;

    //�X�V
    virtual void Update(float deltaTime)override;
    virtual void LateUpdate(float deltaTime)override;
    //�`��
    virtual void Draw()const override;
    //�ڐG����
    virtual void React(Actor& other)override;

    virtual void ChangeState(int state);
    virtual int CurrentState();
    virtual void MovePosition(float deltaTime);

    virtual void IsAttack(bool isAttack);
    virtual bool IsAttack();

    virtual IWorld* World();
protected:
    
    virtual void Debug(float deltaTime)override;

    StateMachine states_;
    bool isAttack_{ false };
};
#endif
