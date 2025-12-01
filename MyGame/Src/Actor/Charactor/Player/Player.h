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
    //============以下プレイヤー状態管理============
    void SetGuard(bool guard);
    bool IsGuard();

    void SetParryEnable(bool enable);
    bool CanUseParry();

    void SetParry(bool parry);
    bool IsParry();

    bool IsSkillUsable();
    void AddSkillPoint(float point);
    void ReduceSkillPoint(float point);
    void SetSkillPoint(float point);
    float CurrentSkillPoint() const;
    float MaxSkillPoint() const;

    void AddGuardPoint(float point);
    void ReduceGuardPoint(float point);
    void ResetGuardPoint();
    float CurrentGuardPoint() const;
    float MaxGuardPoint() const;
    
    bool IsGuardBroken() const;

    void SetTimeScale(float slowTime,float affectTime = 0.0f);
    //スケールがデフォルトの値か？
    bool IsTimeScaleDefault();
    CameraController* GetPlayerCamera();
    void Debug(float deltaTime)override;
    //攻撃処理
    void TestAttack();
    void UltimateATK();
    //ガードブレイクUIを表示するか？
    bool IsDrawGuardBreakUI() const;
    //ガード回復可能時間をリセット
    void ResetGuardHealTime();
private:
    GSvector3 GetCameraDirection();
    float GetCameraHorizontalRadian();
    GStransform& CameraTransform();
    void MoveCamera(float deltaTime);
    void MoveColliders();
    bool CanHealGuardPoint() const;
    void RegenerateGuard(float deltaTime);
    
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
    bool canUseParry_{ false };
    //パリィ中か
    bool isParry_{ false };
    //ガード耐久値を回復できるか
    bool canHealGuard_;
    //ガード回復できるようになる時間
    float guardHealTimer_{ 0.0f };
    const float guardHealDelay_{ 2.0f };
    //パリィ判定
    ParryCollider* parryCollider_{ nullptr };
    //プレイヤーUI表示
    PlayerUI* ui_ = nullptr;

    //スキルポイント
    float skillPt_{ 50 };
    const float maxSkillPt_{ 100 };

    //ガード耐久値
    float guardPt_{ 10 };
    const float maxGuardPt_{ 10 };
};
#endif
