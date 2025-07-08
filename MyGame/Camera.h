#ifndef CAMERA_H_
#define CAMERA_H_

class IWorld;

#include <GStransform.h>
#include <gslib.h>

class Camera
{
public:
    struct Plane {
        float a, b, c, d;
        void normalize() {
            float len = sqrt(a * a + b * b + c * c);
            a /= len; b /= len; c /= len; d /= len;
        }
        float distance(float x, float y, float z) const {
            return a * x + b * y + c * z + d;
        }
    };
    Camera(IWorld* world = nullptr, int id = 0);
    void Update(float deltaTime);
    void Draw() const;
    void Debug(float deltaTime);
    void SetPriority(float priority);
    int GetPriority();
    void SetPosition(GSvector3 position,bool Smooth = true);
    void SetRotate(GSvector3 rotate);
    void SetEulerAngle(const GSvector3& euler);
    void View(GSvector3 target);
    GSvector3 GetPosition();
    GSvector3 GetRotate();
    GStransform& Transform();
    void ViewRange(GSvector2 range, GSvector2 offset);
    GLint ViewPort(int id);
    const GSmatrix4& GetProjectionMatrix();
    const GSmatrix4& GetViewMatrix();
    GSvector3 CalculatePosition(GSvector3 target,float distance, float azimuthDeg, float elevationDeg);
    bool IsInversion();
    //指定範囲内か？
    bool IsVisible(const GSvector3 pos , float radius = 0.0f);
    //視錐台カリング
    bool InFrustum(const GSvector3 pos, float radius = 0.0f);
    GSvector2 GetViewSize();
    float GetFov();
    void SetFov(const int fov);
    int GetID();
    //カメラの優先順位
    enum Priority {
        Disable,
        Player,
        IsDebug,
        Event
    };
private:
    GSmatrix4 projection_;
    GSmatrix4 view_;
    //float lerpTime_;
    //カメラID（登録順）
    int id_{ 0 };
    void FreeMode();
    /*void TPSMode();
    void OrbitMode();*/
    float distance_{ 15 };
    /// <summary>
    /// 優先度:0=無効, 1=デフォルト
    /// </summary>
    int priority_{ 1 };
    //デバック用描画モード
    enum Mode {
        Free,
        Orbit,
        TPS
    };
    int debugMode_{ 0 };
    int cameraAzimuths_{ 0 };
    //フォグ、画面比率設定(3:2)
    float fov_{ 45.0f }, width_{ 1280 }, height_{ 720 };
    float deltaTimer_{ 0 };
    IWorld* world_{ nullptr };
    GStransform transform_;
    GSvector3 velocity_{ 0.0f,0.0f,0.0f };
    //GSvector3 position_ {0, 0, 0};
    GSvector3 target_{0, 0, 0};
    GSvector3 rotate_{ 0, 0, 0 };
    GSvector2 viewRange_, viewOffset_;
    bool isDebug_{ false };
};
#endif
