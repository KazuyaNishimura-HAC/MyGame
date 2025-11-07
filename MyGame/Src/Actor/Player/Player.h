#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <GStransform.h>
#include "../Charactor.h"
class GUI;
class PlayerUI;
class CameraController;
class Player : public Charactor
{
public:
    enum Motion {
        Idle,
        Run,
        Attack,
        Combo2,
        Combo3,
        Attack2,
        SkillCoolTime,
        AttackSkill,
        UltSkill,
        Parry,
        Hit,
        Death,
        Death2,
        Death3
    };
    //コンストラクタ
    Player(IWorld* world = nullptr,const GSvector3& position = {0, 0, 0},Status status = Status(), GSuint mesh = Model::Player);
    //デストラクタ
    ~Player()override;

    //更新
    void Update(float deltaTime)override;
    void LateUpdate(float deltaTime)override;
    //描画
    void Draw()const override;
    //接触判定
    void React(Actor& other)override;
    void TakeDamage(float damage)override;
    void MovePosition(float deltaTime);
    void Debug(float deltaTime)override;
private:
    GSvector3 GetCameraDirection();
    float GetCameraHorizontalRadian();
    GStransform& CameraTransform();
    void MoveCamera(float deltaTime);
    void MoveAttackCollide();
    void TestAttack();
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

    PlayerUI* ui_ = nullptr;
};
#endif
