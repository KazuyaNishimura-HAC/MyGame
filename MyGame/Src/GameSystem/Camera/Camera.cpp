#include "Camera.h"
#include "../InputSystem/InputSystem.h"
#include "../../Screen.h"
#include <imgui/imgui.h>
#include <string>
#include <GSeffect.h>
#include <array>

Camera::Camera(IWorld* world,int id)
{
    world_ = world;
    viewRange_ = Screen::WindowsScreen();
    viewOffset_ = { 0,0 };
    id_ = id;
}

void Camera::Update(float deltaTime)
{
    //視錐台カリング
    gsUpdateFrustum();
    //コントローラーが存在しなかったら移動しない
    if (!controller_) return;

    View currentView;
    if(controller_->IsShake()) currentView = controller_->GetAffectedView();
    else currentView = controller_->GetView();
     
    SetView(currentView,deltaTime);
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
    glViewport(viewOffset_.x, viewOffset_.y, viewRange_.x, viewRange_.y);
    glLoadIdentity();
    gluLookAt
    (
        eye.x, eye.y, eye.z,
        at.x, at.y, at.z,
        up.x, up.y, up.z
    );

    // エフェクト用のカメラを設定
    gsSetEffectCamera();
    // 透視変換行列の取得
    glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat*)&projection_);
    // 視点変換行列の取得
    glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&view_);
}

void Camera::Debug()
{
    //なんかシーン遷移するとnullになる後で直せ
    if (!controller_) return;

    ImGui::Begin("CurrentCamera");
    ImGui::Text("%s", ("Priority : " + controller_->GetPriorityName()).c_str());
    ImGui::InputFloat3("Position", transform_.position());
    ImGui::DragFloat3("Rotation", transform_.eulerAngles());
    ImGui::InputFloat3("LookAt", transform_.position() + transform_.forward());
    ImGui::InputFloat3("UP", transform_.up());
    ImGui::InputFloat("FoV", &fov_);
    ImGui::InputFloat("SmoothTime",&smoothTime_);
    ImGui::End();

    CameraShake debugShake = controller_->GetShake();
    ImGui::Begin("ShakeValues");
    ImGui::InputFloat("Timer", &debugShake.timer);
    ImGui::InputFloat("Strength", &debugShake.strength);
    ImGui::InputFloat("DecayTime", &debugShake.decayTime);
    ImGui::InputFloat("DecaySpeed", &debugShake.decaySpeed);
    ImGui::InputFloat("HZ", &debugShake.hz);
    ImGui::InputFloat2("AffectVec", debugShake.affectVector);
    ImGui::InputFloat("AffectFov", &debugShake.affectFov);
    ImGui::End();
}

CameraController::Priority Camera::GetPriority()
{
    return controller_->GetPriority();
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

int Camera::GetID()
{
    return id_;
}

bool Camera::IsDead()
{
    return false;
}

void Camera::SetController(CameraController* controller)
{
    controller_ = controller;
}

void Camera::SetView(View view,float deltaTime)
{
    
    //瞬間的な移動かどうか
    if (!view.isSmooth) {
        transform_.position(view.pos);
    }
    else {
        smoothTime_ = view.smoothTime;
        const float MaxSpeed{ 100 };       // 移動スピードの最大値
        GSvector3 pos = GSvector3::smoothDamp(transform_.position(), view.pos, velocity_, smoothTime_, MaxSpeed, deltaTime);
        transform_.position(pos);
    }
    
    transform_.lookAt(view.tar);
    fov_ = view.fov;
}

