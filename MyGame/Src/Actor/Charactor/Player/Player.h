#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <GStransform.h>
#include "../Charactor.h"
#include "../../../GameSystem/BattleSystem/BattleManager.h"
class GUI;
class PlayerUI;
class CameraController;
class ParryCollider;
class EnemyDetectionCollider;
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
    void MoveCamera(float deltaTime);
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

    void SetEnemyNearby(bool flg);
    bool IsEnemyNearby() const;

    void SetTimeScale(float slowTime,float affectTime = 0.0f);
    //スケールがデフォルトの値か？
    bool IsTimeScaleDefault();
    CameraController* GetPlayerCamera();
    void Debug(float deltaTime)override;
    //攻撃処理
    void NormalAttack();
    void UltimateATK();
    //ガードブレイクUIを表示するか？
    bool IsDrawGuardBreakUI() const;
    //ガード回復可能時間をリセット
    void ResetGuardHealTime();
    //攻撃時の前進移動
    void AttackMove(float deltaTime);
    //今向いている方向に前進
    void MoveForward(float value);
    //入力の方向取得
    GSvector3 GetInputDirection() const;
    //一番近くの敵座標を設定
    void SetNearbyEnemyPos(GSvector3 position);
    //一番近い敵との距離
    float NearstEnemyDist() const;
    //瞬間的に向く方向を決める
    void UpdateDirection();
    //コンボ数取得
    int GetCurrentCombo() const;
    int GetMaxCombo() const;
    void ResetCombo();
private:
    GSvector3 GetCameraDirection() const;
    float GetCameraHorizontalRadian();
    GStransform& CameraTransform() const;
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
    //カメラの回転速度
    float cameraRotateSpeed_{ 3.0f };
    //以下プレイヤー動作値
    float moveSpeed_{ 0.15f };
    //ガード中か
    bool isGuard_{ false };
    //パリィ可能か
    bool canUseParry_{ false };
    //パリィ中か
    bool isParry_{ false };
    //ガード耐久値を回復できるか
    bool canHealGuard_{ false };
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

    //周辺に敵がいるか
    bool isEnemyNearby_{ false };
    //範囲内で一番近い敵の座標
    GSvector3 nearbyEnemyPos_{ 0,0,0 };
    GSvector3 forwardPosition_{ 0,0,0 };
    //標的検知コライダー
    EnemyDetectionCollider* detectionCollider_;

    //コンボ数
    int combo_{ 0 };
    //最大コンボ数
    int maxCombo_{ 0 };

    ResultData resultData_{};
};
#endif
