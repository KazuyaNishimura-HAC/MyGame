#include "Camera.h"
#include "../InputSystem/InputSystem.h"
#include "../../Screen.h"
#include <imgui/imgui.h>
#include <GSeffect.h>
#include <array>
const double PI{ 3.1415926535f };
Camera::Camera(IWorld* world,int id)
{
    world_ = world;
    delete world;
    viewRange_ = Screen::WindowsScreen();
    viewOffset_ = { 0,0 };
    priority_ = IsDebug;
    debugMode_ = Free;
    id_ = id;
}

void Camera::Update(float deltaTime)
{
    deltaTimer_ = deltaTime;
#if  _DEBUG
    if (priority_ == IsDebug) {
        ImGui::Begin("Camera");
        ImGui::InputFloat3("Position", transform_.position());
        ImGui::DragFloat3("Rotation", transform_.eulerAngles());
        ImGui::InputFloat3("LookAt", transform_.position() + transform_.forward());
        ImGui::InputFloat3("UP", transform_.up());
        ImGui::InputFloat("FoV", &fov_);
        ImGui::InputInt("Mode", &debugMode_);
        debugMode_ = CLAMP(debugMode_,0,1);
        if (ImGui::Button("Close")) {
            priority_ = Player;
        }
        ImGui::End();
    }
    
    if (priority_ != IsDebug && InputSystem::DebugInput())
    {
        SetPriority(IsDebug);
    }
    Debug(deltaTime);
#endif
}

void Camera::Draw() const
{
    GSvector3 eye = transform_.position();
    GSvector3 at = eye + transform_.forward();
    GSvector3 up = transform_.up();
    // 透視射影の変換行列を設定する
    glMatrixMode(GL_PROJECTION);
    //投影変換の変換行列を単位行列で初期化
    glLoadIdentity();
    gluPerspective(fov_, viewRange_.x / viewRange_.y, 0.3f, 1000.0f);
    // モデルビューモードにする
    glMatrixMode(GL_MODELVIEW);
    ////オフセットは左下基準
    //glViewport(viewOffset_.x, viewOffset_.y, viewRange_.x, viewRange_.y);
    glLoadIdentity();
    gluLookAt
    (
        eye.x, eye.y, eye.z,
        at.x, at.y, at.z,
        up.x, up.y, up.z
    );

    // エフェクト用のカメラを設定
    //gsSetEffectCamera();
    // 透視変換行列の取得
    glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat*)&projection_);
    // 視点変換行列の取得
    glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&view_);
}

void Camera::Debug(float deltaTime)
{
    if (priority_ != IsDebug) return;
    if (debugMode_ == Free) FreeMode();
    /*if (debugMode_ == Orbit) OrbitMode();
    if (debugMode_ == TPS)   TPSMode();*/
}

void Camera::SetPriority(float priority)
{
    priority_ = priority;
}

int Camera::GetPriority()
{
    return priority_;
}

void Camera::SetPosition(GSvector3 position,bool Smooth)
{
    //瞬間的な移動かどうか
    if (!Smooth) {
        transform_.position(position);
        return;
    }
    // スムースダンプによる滑らかな補間
    const float SmoothTime{ 6.0f };    // 補間フレーム数
    const float MaxSpeed{ 100 };       // 移動スピードの最大値
    GSvector3 pos = GSvector3::smoothDamp(transform_.position(), position, velocity_,SmoothTime, MaxSpeed, deltaTimer_);
    transform_.position(pos);
}

void Camera::SetRotate(GSvector3 rotate)
{
    transform_.rotate(rotate);
}

void Camera::SetEulerAngle(const GSvector3& euler)
{
    transform_.localEulerAngles(euler);
}

void Camera::View(GSvector3 target)
{
    transform_.lookAt(target,transform_.up());
}

GSvector3 Camera::GetPosition()
{
    return transform_.position();
}

GSvector3 Camera::GetRotate()
{
    return transform_.eulerAngles();
}

GStransform& Camera::Transform()
{
    return transform_;
}

void Camera::ViewRange(GSvector2 range, GSvector2 offset)
{
    viewRange_ = range;
    viewOffset_ = offset;
}

GLint Camera::ViewPort(int id)
{
    std::array<GLint, 4> viewPort = { (GLint)viewOffset_.x, (GLint)viewOffset_.y, (GLint)viewRange_.x, (GLint)viewRange_.y };
    return viewPort[id];
}

const GSmatrix4& Camera::GetProjectionMatrix()
{
    return projection_;
}

const GSmatrix4& Camera::GetViewMatrix()
{
    return view_;
}


GSvector3 Camera::CalculatePosition(GSvector3 target,float distance, float azimuthDeg, float elevationDeg) {
    float azimuth = azimuthDeg * (PI / 180.0f);
    float elevation = elevationDeg * (PI / 180.0f);

    GSvector3 pos;
    pos.x = target.x + distance * cosf(elevation) * sinf(azimuth);
    pos.y = target.y + distance * sinf(elevation);
    pos.z = target.z + distance * cosf(elevation) * cosf(azimuth);
    SetPosition(pos,false);
    return pos;
}
//カメラが反転しているか
bool Camera::IsInversion()
{
    return transform_.up().y <= 0.0f;
}

bool Camera::IsVisible(const GSvector3 pos, float radius)
{
    int distance;
    GSvector3 cameraPos = transform_.position();
    distance = gsVector3Distance(&cameraPos, &pos);
    if (distance < 1000) return true;
    return false;

}

bool Camera::InFrustum(const GSvector3 pos, float radius)
{
    float proj[16], model[16], clip[16];
    glGetFloatv(GL_PROJECTION_MATRIX, proj);
    glGetFloatv(GL_MODELVIEW_MATRIX, model);
    // 乗算結果（clip = proj * modelview）
    for (int i = 0; i < 16; ++i) clip[i] = 0;

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            for (int k = 0; k < 4; ++k) {
                clip[row * 4 + col] += model[row * 4 + k] * proj[k * 4 + col];
            }
        }
    }      
    Plane frustum_[6];
    // 各平面抽出
    // LEFT
    frustum_[0] = { clip[3] + clip[0], clip[7] + clip[4], clip[11] + clip[8], clip[15] + clip[12] };
    // RIGHT
    frustum_[1] = { clip[3] - clip[0], clip[7] - clip[4], clip[11] - clip[8], clip[15] - clip[12] };
    // BOTTOM
    frustum_[2] = { clip[3] + clip[1], clip[7] + clip[5], clip[11] + clip[9], clip[15] + clip[13] };
    // TOP
    frustum_[3] = { clip[3] - clip[1], clip[7] - clip[5], clip[11] - clip[9], clip[15] - clip[13] };
    // NEAR
    frustum_[4] = { clip[3] + clip[2], clip[7] + clip[6], clip[11] + clip[10], clip[15] + clip[14] };
    // FAR
    frustum_[5] = { clip[3] - clip[2], clip[7] - clip[6], clip[11] - clip[10], clip[15] - clip[14] };

    // 正規化
    for (int i = 0; i < 6; ++i) frustum_[i].normalize();

    for (int i = 0; i < 6; ++i) {
        if (frustum_[i].distance(pos.x, pos.y, pos.z) < -radius) {
            //範囲外
            return false; 
        }
    }
    return true;
}

GSvector2 Camera::GetViewSize()
{
    return viewRange_;
}

float Camera::GetFov()
{
    return fov_;
}

void Camera::SetFov(const int fov)
{
    fov_ = fov;
}

int Camera::GetID()
{
    return id_;
}

void Camera::FreeMode()
{
    float yaw = 0;
    float up = 0;
    if (gsGetKeyState(GKEY_I)) up = -2 * deltaTimer_;
    if (gsGetKeyState(GKEY_J)) yaw = 2 * deltaTimer_;
    if (gsGetKeyState(GKEY_K)) up = 2 * deltaTimer_;
    if (gsGetKeyState(GKEY_L)) yaw = -2 * deltaTimer_;
    transform_.rotate(up, yaw, 0.0f);
    GSvector3 velocity{ 0,0,0 };
    if (gsGetKeyState(GKEY_W)) velocity.z = 5 * deltaTimer_;
    if (gsGetKeyState(GKEY_S)) velocity.z = -5 * deltaTimer_;
    if (gsGetKeyState(GKEY_A)) velocity.x = 5 * deltaTimer_;
    if (gsGetKeyState(GKEY_D)) velocity.x = -5 * deltaTimer_;
    transform_.translate(velocity);
}

//void Camera::TPSMode()
//{
//    Charactor* player = world_->GetCharactor(0);
//    const GSvector3 cameraOffset{ 0,6,15 };
//    const GSvector3 playerOffset{ 0,6,0 };
//    SetEulerAngle(player->Transform().eulerAngles());
//    //カメラ後ろ振り向き
//    SetPosition(cameraOffset * player->Transform().localToWorldMatrix());
//    View(playerOffset * transform_.localToWorldMatrix());
//}
//
//void Camera::OrbitMode()
//{
//    const GSvector3 playerOffset{ 0,6,0 };
//    if (gsGetKeyState(GKEY_W)) distance_ += deltaTimer_;
//    if (gsGetKeyState(GKEY_A)) cameraAzimuths_ += deltaTimer_;
//    if (gsGetKeyState(GKEY_S)) distance_ -= deltaTimer_;
//    if (gsGetKeyState(GKEY_D)) cameraAzimuths_ -= deltaTimer_;
//
//    Charactor* player = world_->GetCharactor(0);
//    SetEulerAngle(player->Transform().eulerAngles());
//    CalculatePosition(
//        playerOffset * player->Transform().localToWorldMatrix(),
//        distance_,
//        cameraAzimuths_,
//        0
//    );
//    View(player->Transform().position());
//}
