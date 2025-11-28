#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <GStransform.h>
#include "../Charactor.h"
class GUI;
class PlayerUI;
class CameraController;
class ParryCollider;
class Player : public Charactor
{
public:
    
    //コンストラクタ
    Player(IWorld* world = nullptr,const GSvector3& position = {0, 0, 0}, const GSvector3& rotate = { 0, 0, 0 }, Status status = {}, GSuint mesh = Model::Player);
    //デストラクタ
    ~Player()override;

    //更新
    void Update(float deltaTime)override;
    void LateUpdate(float deltaTime)override;
    //描画
    void Draw()const override;
    //接触判定
    void React(Actor& other)override;
    void OnAttackHit()override;
    void HitAttackCollider(const AttackInfo& info)override;
    void MovePosition(float deltaTime);
    void SetGuard(bool guard);
    bool IsGuard();
    void SetParryEnable(bool enable);
    bool IsParryEnable();
    void SetParry(bool parry);
    bool IsParry();
    bool IsSkillUsable();
    void SetSkillPoint(float point);
    float CurrentSkillPoint();
    float MaxSkillPoint();
    

    void SetTimeScale(float slowTime,float affectTime = 0.0f);
    //スケールがデフォルトの値か？
    bool IsTimeScaleDefault();
    CameraController* GetPlayerCamera();
    void Debug(float deltaTime)override;
    void TestAttack();
    void UltimateATK();
private:
    GSvector3 GetCameraDirection();
    float GetCameraHorizontalRadian();
    GStransform& CameraTransform();
    void MoveCamera(float deltaTime);
    void MoveColliders();
    
    //カメラコントローラー
    CameraController* camera_{ nullptr };

    //カメラの角度(初期値)
    GSvector3 cameraRotation_{ 0,-90,0 };
    //カメラ初期座標
    GSvector3 cameraOffset_{ 0,2.0f,0 };
    //注視点Offset
    GSvector3 cameraFocusOffset_{ 0,1.5f,0 };
    //注視点までの距離
    float cameraDepth_{ 5.5f };
    //以下プレイヤー動作値
    float moveSpeed_{ 1.5f };
    //ガード中か
    bool isGuard_{ false };
    //パリィ可能か
    bool isParryEnable_{ false };
    //パリィ中か
    bool isParry_{ false };
    //必殺技を使えるか
    bool isUltimate{ false };

    //パリィ判定
    ParryCollider* parryCollider_{ nullptr };
    //プレイヤーUI表示
    PlayerUI* ui_ = nullptr;

    //スキルポイント
    int skillPt_{ 50 };
    const int maxSkillPt_{ 100 };
};
#endif
