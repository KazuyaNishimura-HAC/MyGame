#ifndef DEBUG_CAMERA_H_
#define	DEBUG_CAMERA_H_

#include <GStransform.h>

class IWorld;
class CameraController;
class Camera;

class DebugCamera {
public:
    DebugCamera(IWorld* world);
    ~DebugCamera();
    void Update(float deltaTime);
    void Draw()const;
    void DrawImGui();
private:
    void FreeMode(float deltaTime);
    void FocusMode(float deltaTime);
    GSvector3 CalculatePosition(GSvector3 target, float distance, float azimuthDeg, float elevationDeg);

    enum Mode {
        Free,
        Focus
    };
    IWorld* world_{ nullptr };
    CameraController* camera_{ nullptr };
    GStransform transform_;
    GSvector3 position_{ 0,0,0 };
    GSvector3 target_{ 0,0,0 };
    int mode_{ Mode::Free };
    float cameraDistance_{ 0 };
    float cameraAzimuths_{ 0 };
    bool isDebug_{ false };
};
#endif
