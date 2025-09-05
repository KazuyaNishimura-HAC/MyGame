#include "DebugCamera.h"
#include "CameraController.h"
#include "../../World/IWorld.h"
#include "../../Actor/Player/Player.h"
const double PI{ 3.1415926535f };

DebugCamera::DebugCamera(IWorld* world)
	:world_{ world }
{
	camera_ = new CameraController(CameraController::Disable,0);
    world_->AddCameraController(camera_);
}

DebugCamera::~DebugCamera()
{

}

void DebugCamera::Update(float deltaTime)
{
    if (!world_->IsDebug()) return;
    camera_->SetPriority(CameraController::Debug);
    switch (mode_) {
    case Mode::Free:
        FreeMode(deltaTime);
        break;
    case Mode::Focus:
        FocusMode(deltaTime);
        break;
    default:
        break;
    }
	camera_->SetView(position_,target_);
}

void DebugCamera::Draw() const
{

}

void DebugCamera::FreeMode(float deltaTime)
{
    float yaw = 0;
    float up = 0;
    if (gsGetKeyState(GKEY_I)) up = -2 * deltaTime;
    if (gsGetKeyState(GKEY_J)) yaw = 2 * deltaTime;
    if (gsGetKeyState(GKEY_K)) up = 2 * deltaTime;
    if (gsGetKeyState(GKEY_L)) yaw = -2 * deltaTime;
    transform_.rotate(up, yaw, 0.0f);
    GSvector3 velocity{ 0,0,0 };
    if (gsGetKeyState(GKEY_W)) velocity.z = 0.25f * deltaTime;
    if (gsGetKeyState(GKEY_S)) velocity.z = -0.25f * deltaTime;
    if (gsGetKeyState(GKEY_A)) velocity.x = 0.25f * deltaTime;
    if (gsGetKeyState(GKEY_D)) velocity.x = -0.25f * deltaTime;
    transform_.translate(velocity);
    position_ = transform_.position();
    target_ = transform_.position() + transform_.forward();
}

void DebugCamera::FocusMode(float deltaTime)
{
    Player* player = world_->GetPlayer();
    GSvector3 playerPos = player->Transform().position();
    const GSvector3 offsetPos = { 0,4,0 };

    if (gsGetKeyState(GKEY_W)) cameraDistance_ += deltaTime;
    if (gsGetKeyState(GKEY_A)) cameraAzimuths_ += deltaTime;
    if (gsGetKeyState(GKEY_S)) cameraDistance_ -= deltaTime;
    if (gsGetKeyState(GKEY_D)) cameraAzimuths_ -= deltaTime;

    position_ = offsetPos * player->Transform().localToWorldMatrix(),
    position_ = CalculatePosition(position_, cameraDistance_, cameraAzimuths_,0);
    target_ = playerPos;
}

GSvector3 DebugCamera::CalculatePosition(GSvector3 target,float distance, float azimuthDeg, float elevationDeg) {
    float azimuth = azimuthDeg * (PI / 180.0f);
    float elevation = elevationDeg * (PI / 180.0f);

    GSvector3 pos;
    pos.x = target.x + distance * cosf(elevation) * sinf(azimuth);
    pos.y = target.y + distance * sinf(elevation);
    pos.z = target.z + distance * cosf(elevation) * cosf(azimuth);
    return pos;
}
