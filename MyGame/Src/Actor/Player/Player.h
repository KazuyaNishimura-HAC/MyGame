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
    //コンストラクタ
    Player(IWorld* world = nullptr, GSuint mesh = Model::Player);
    Player(IWorld* world, GSuint mesh,const GSvector3& position);
    //デストラクタ
    ~Player()override;

    //更新
    virtual void Update(float deltaTime)override;
    virtual void LateUpdate(float deltaTime)override;
    //描画
    void Draw()const override;
    //接触判定
    void React(Actor& other)override;
    
    void ChangeState(int state);
    int CurrentState();
    void MovePosition(float deltaTime);
    
    void IsAttack(bool isAttack);
    bool IsAttack();

    IWorld* World();
    void Debug(float deltaTime)override;
private:
    GSvector3 GetCameraDirection();
    float GetCameraHorizontalRadian();
    GStransform& CameraTransform();
    void MoveCamera(float deltaTime);

    StateMachine states_;
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
    bool isAttack_{ false };
};
#endif
