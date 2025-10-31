#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <GStransform.h>
#include "../Charactor.h"

class GUI;
class CameraController;

class Player : public Charactor
{
public:
    //�R���X�g���N�^
    Player(IWorld* world = nullptr,const GSvector3& position = {0, 0, 0}, GSuint mesh = Model::Player);
    //�f�X�g���N�^
    ~Player()override;

    //�X�V
    void Update(float deltaTime)override;
    void LateUpdate(float deltaTime)override;
    //�`��
    void Draw()const override;
    //�ڐG����
    void React(Actor& other)override;
    void MovePosition(float deltaTime);
    void Debug(float deltaTime)override;
private:
    GSvector3 GetCameraDirection();
    float GetCameraHorizontalRadian();
    GStransform& CameraTransform();
    void MoveCamera(float deltaTime);
    void AttackCollide();
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
    float moveSpeed_{ 1.5f };
    bool isAttack_{ false };
};
#endif
