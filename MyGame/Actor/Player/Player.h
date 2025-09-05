#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include "../Actor.h"
#include "../../AssetID/Model.h"
#include "../../State/StateMachine.h"

class GUI;
class CameraController;

class Player : public Actor
{
public:
    //�R���X�g���N�^
    Player(IWorld* world = nullptr, GSuint mesh = Model::Player);
    Player(IWorld* world, GSuint mesh,const GSvector3& position);
    //�f�X�g���N�^
    ~Player()override;

    //�X�V
    virtual void Update(float deltaTime)override;
    virtual void LateUpdate(float deltaTime)override;
    //�`��
    void Draw()const override;
    //�ڐG����
    void React(Actor& other)override;

    void Debug(float deltaTime)override;
private:
    StateMachine states_;
    CameraController* camera_{ nullptr };
};
#endif
