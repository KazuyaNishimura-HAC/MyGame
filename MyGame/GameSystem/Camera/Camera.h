#ifndef CAMERA_H_
#define CAMERA_H_

#include <GStransform.h>
#include <gslib.h>
#include "CameraController.h"

class IWorld;

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
    void Debug();
    CameraController::Priority GetPriority();
    GStransform& Transform();
    void ViewRange(GSvector2 range, GSvector2 offset);
    GLint ViewPort(int id);
    const GSmatrix4& GetProjectionMatrix();
    const GSmatrix4& GetViewMatrix();
    
    bool IsInversion();
    //指定範囲内か？
    bool IsVisible(const GSvector3 pos , float radius = 0.0f);
    //視錐台カリング
    bool InFrustum(const GSvector3 pos, float radius = 0.0f);
    GSvector2 GetViewSize();
    int GetID();
    bool IsDead();
    void SetController(CameraController* controller_);
private:
    void SetView(View view);
    CameraController* controller_{ nullptr };

    GSmatrix4 projection_;
    GSmatrix4 view_;
    //float lerpTime_;
    //カメラID（登録順）
    int id_{ 0 };
    float distance_{ 15 };
    int cameraAzimuths_{ 0 };
    float fov_{ 45.0f };
    //画面比率設定(3:2)
    float width_{ 1280 }, height_{ 720 };
    IWorld* world_{ nullptr };
    GStransform transform_;
    GSvector3 velocity_{0,0,0};
    GSvector2 viewRange_, viewOffset_;
    float deltaTimer_{ 0.0f };
};
#endif
