#include "Player.h"
#include <imgui/imgui.h>
#include "../../Actor/Model.h"
#include "../../World/IWorld.h"
#include "../../GameSystem/Camera/Camera.h"
#include "../../GameSystem/InputSystem/InputSystem.h"
#include "../../GameSystem/Field/FieldManager.h"
#include "../../GameSystem/Field/Ray.h"
//ステートヘッダー
#include "State/PlayerIdle.h"
#include "State/PlayerMove.h"
#include "State/PlayerAttack.h"
#include "State/PlayerUltimateSkill.h"
Player::Player(IWorld* world, GSuint mesh)
    :Actor(mesh)
{
    world_ = world;
    name_ = ActorName::Player;
    //ステートの追加
    states_.AddState(PlayerState::Idle, new PlayerIdle(this));
    states_.AddState(PlayerState::Move, new PlayerMove(this));
    states_.AddState(PlayerState::Attack, new PlayerAttack(this));
    states_.AddState(PlayerState::Ultimate, new PlayerUltimateSkill(this));
    states_.ChangeState(PlayerState::Idle);

    mesh_->AddEvent(2, 60, [=] {AttackCollide(); });

    colliderOffset_ = { 0.0f,1.0f,0.0f };
    camera_ = new CameraController(CameraController::Player);
    world_->AddCameraController(camera_);
    camera_->SetSmooth(true);
}

Player::Player(IWorld* world, GSuint mesh, const GSvector3& position)
    :Player{ world, mesh }
{
    //初期座標設定
    transform_.position(position);
}
Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    Actor::Update(deltaTime);
    states_.Update(deltaTime);
    collider_.Position(transform_.position() + colliderOffset_);

    if (!IsAttack() && InputSystem::ButtonTrigger(InputSystem::Button::B)) {
        states_.ChangeState(PlayerState::Attack);
        camera_->SetShakeValues(180.0f, 1.0f, 160.0f, 1.0f, 20.0f, { 0.1f,0.1f }, 0.0f);
    }
    if (!IsAttack() && InputSystem::ButtonTrigger(InputSystem::Button::A)) {
        states_.ChangeState(PlayerState::Ultimate);
    }
    MoveCamera(deltaTime);
}
void Player::LateUpdate(float deltaTime)
{
    Actor::LateUpdate(deltaTime);
}
//描画
void Player::Draw()const
{
    Actor::Draw();
    collider_.Draw();
}

void Player::React(Actor& other)
{

}

void Player::ChangeState(int state)
{
    states_.ChangeState(state);
}

int Player::CurrentState()
{
    return states_.CurrentState();
}
void Player::IsAttack(bool isAttack)
{
    isAttack_ = isAttack;
}
bool Player::IsAttack()
{
    return isAttack_;
}

void Player::MovePosition(float deltaTime)
{
    GSvector2 input = InputSystem::LeftStick() * 0.1f * deltaTime;

    GSvector3 forward = CameraTransform().forward();
    GSvector3 right = CameraTransform().right();
    // Y成分は無視してXZ平面に投影
    forward.y = 0;
    right.y = 0;
    forward.normalize();
    right.normalize();

    // 入力をカメラ方向に変換
    GSvector3 moveDirection = (forward * input.y) + (right * input.x);
    moveDirection.normalize();
    //入力rawを移動の強さにする
    float magnitude = input.magnitude();

    GSvector3 moveVector = moveDirection * magnitude * moveSpeed_ * deltaTime;

    //プレイヤーを滑らかに回転
    if (input != GSvector2::zero())
    {
        //向きの補間
        GSquaternion rotation =
            GSquaternion::rotateTowards(
                transform_.rotation(),
                GSquaternion::lookRotation(moveDirection), 15.0f * deltaTime);
        transform_.rotation(rotation);
    }

    // 平行移動する（ワールド基準）
    transform_.translate(moveVector, GStransform::Space::World);
}

void Player::MoveCamera(float deltaTime)
{
    float yaw = 0, pitch = 0;
    yaw = InputSystem::RightStick().x  * 3 * deltaTime;
    pitch = InputSystem::RightStick().y * 3 * deltaTime;
    cameraRotation_.y -= yaw;
    cameraRotation_.x -= pitch;
    cameraRotation_.x = CLAMP(cameraRotation_.x, 0.0f, 20.0f);

    float yawRad = DEG_TO_RAD(cameraRotation_.y);
    float pitchRad = DEG_TO_RAD(cameraRotation_.x);

    GSvector3 offset;
    offset.x = cos(pitchRad) * sin(yawRad);
    offset.y = sin(pitchRad);
    offset.z = cos(pitchRad) * cos(yawRad);

    GSvector3 cameraPos = transform_.position() + cameraOffset_ + (offset * cameraDepth_);
    GSvector3 target = transform_.position() + cameraFocusOffset_;
    
    camera_->SetView(cameraPos,target);
}

void Player::AttackCollide()
{
    int test = 0;
}

//現在のカメラの方向を取得
GSvector3 Player::GetCameraDirection()
{
    return GSvector3(sin(DEG_TO_RAD(cameraRotation_.y)), sin(DEG_TO_RAD(cameraRotation_.x)), cos(DEG_TO_RAD(cameraRotation_.y))).normalized();
}

float Player::GetCameraHorizontalRadian()
{
    return DEG_TO_RAD(world_->GetCamera()->Transform().eulerAngles().y);
}

GStransform& Player::CameraTransform()
{
    return world_->GetCamera()->Transform();
}

IWorld* Player::World()
{
    return world_;
}

void Player::Debug(float deltaTime)
{
    mesh_->Debug();
}
