#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <GStransform.h>
#include "../Charactor.h"
#include "../Model.h"
#include "../../State/StateMachine.h"

class GUI;
class CameraController;

class Player : public Charactor
{
public:
    //コンストラクタ
    Player(IWorld* world = nullptr,const GSvector3& position = {0, 0, 0}, GSuint mesh = Model::Player);
    //デストラクタ
    ~Player()override;

    //更新
    void Update(float deltaTime)override;
    void LateUpdate(float deltaTime)override;
    //描画
    void Draw()const override;
    //接触判定
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

    //カメラの角度
    GSvector3 cameraRotation_{ 0,0,0 };
    //カメラ初期座標
    GSvector3 cameraOffset_{ 0,2.0f,0 };
    //注視点Offset
    GSvector3 cameraFocusOffset_{ 0,1.5f,0 };
    //注視点までの距離
    float cameraDepth_{ 5.5f };

    //以下プレイヤー動作値
    float moveSpeed_{ 1.5f };
    bool isAttack_{ false };
};
#endif
