#include "DebugCamera.h"
#include "../../GameSystem/InputSystem/InputSystem.h"
#include "CameraController.h"
#include "../../World/IWorld.h"
#include "../../Actor/Player/Player.h"
#include <imgui/imgui.h>
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
    DrawImGui();

    if (!isDebug_) return;
    
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

void DebugCamera::DrawImGui()
{
    if (!world_->IsDebug()) return;

    const std::string buttonText = isDebug_ ? "ON" : "OFF";

    ImGui::Begin("DebugCamera");
    ImGui::Text("DebugMode");
    ImGui::SameLine();
    if (ImGui::Button(buttonText.c_str(), ImVec2(40, 20))) {
        isDebug_ = !isDebug_;
        if(isDebug_) camera_->SetPriority(CameraController::Debug);
        else         camera_->SetPriority(CameraController::Disable);
    }

    ImGui::InputInt("Move", &mode_);
    ImGui::End();
}

void DebugCamera::FreeMode(float deltaTime)
{
    //右クリックしながらカメラ回転
    if (gsGetMouseButtonState(GMOUSE_BUTTON_2)) {
        int mouseX = 0;
        int mouseY = 0;
        GSvector3 mouseVelocity = InputSystem::DebugMouseDelta();
        transform_.rotate(mouseVelocity.y, -mouseVelocity.x,0.0f);
    }
    //前後左右移動
    GSvector3 posVelocity{ 0,0,0 };
    if (gsGetKeyState(GKEY_W)) posVelocity.z = 0.25f * deltaTime;
    if (gsGetKeyState(GKEY_S)) posVelocity.z = -0.25f * deltaTime;
    if (gsGetKeyState(GKEY_A)) posVelocity.x = 0.25f * deltaTime;
    if (gsGetKeyState(GKEY_D)) posVelocity.x = -0.25f * deltaTime;
    transform_.translate(posVelocity);
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
