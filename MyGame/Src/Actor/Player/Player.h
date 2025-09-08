#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <GStransform.h>
#include "../Actor.h"
#include "../Model.h"
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
    
    void ChangeState(int state);
    void MovePosition(float deltaTime);
    
    void IsAttack(bool isAttack);
    bool IsAttack();
    void Debug(float deltaTime)override;
private:
    GSvector3 GetCameraDirection();
    float GetCameraHorizontalRadian();
    GStransform& CameraTransform();
    void MoveCamera(float deltaTime);

    StateMachine states_;
    CameraController* camera_{ nullptr };

    //�J�����̊p�x
    GSvector3 cameraRotation_{ 0,0,0 };
    //�J�����������W
    GSvector3 cameraOffset_{ 0,2.0f,0 };
    //�����_Offset
    GSvector3 cameraFocusOffset_{ 0,1.5f,0 };
    //�����_�܂ł̋���
    float cameraDepth_{ 5.5f };

    //�ȉ��v���C���[����l
    bool isAttack_{ false };
};
#endif
