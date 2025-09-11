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
    void Draw()const override;
    //�ڐG����
    void React(Actor& other)override;

    void ChangeState(int state);
    int CurrentState();
    void MovePosition(float deltaTime);

    void IsAttack(bool isAttack);
    bool IsAttack();

    IWorld* World();
    void Debug(float deltaTime)override;
private:
    StateMachine states_;
    bool isAttack_{ false };
};
#endif
