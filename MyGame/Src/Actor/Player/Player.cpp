#include "Player.h"
#include <imgui/imgui.h>
#include "../../World/IWorld.h"
#include "../../GameSystem/Camera/Camera.h"
#include "../../GameSystem/InputSystem/InputSystem.h"
//�X�e�[�g�w�b�_�[
#include "State/PlayerIdle.h"
#include "State/PlayerMove.h"
#include "State/PlayerAttack.h"
#include "State/PlayerUltimateSkill.h"

Player::Player(IWorld* world, const GSvector3& position, GSuint mesh)
    :Charactor(world, position, mesh)
{
    
    name_ = ActorName::Player;
    //�X�e�[�g�̒ǉ�
    states_.AddState(PlayerState::Idle, new PlayerIdle(this));
    states_.AddState(PlayerState::Move, new PlayerMove(this));
    states_.AddState(PlayerState::Attack, new PlayerAttack(this));
    states_.AddState(PlayerState::Ultimate, new PlayerUltimateSkill(this));
    states_.ChangeState(PlayerState::Idle);

    //�X�L��
    mesh_->AddEvent(6, 60, [=] {AttackCollide(); });

    colliderOffset_ = { 0.0f,1.0f,0.0f };
    camera_ = new CameraController(CameraController::Player);
    world_->AddCameraController(camera_);
    camera_->SetSmooth(true);
}
Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    Charactor::Update(deltaTime);
    collider_.Position(transform_.position() + colliderOffset_);

    if (!IsAttack() && InputSystem::ButtonTrigger(InputSystem::Button::B)) {
        states_.ChangeState(PlayerState::Attack);
        camera_->SetShakeValues(30.0f, 1.0f, 160.0f, 1.0f, 20.0f, { 0.1f,0.1f }, 0.0f);
    }
    if (!IsAttack() && InputSystem::ButtonTrigger(InputSystem::Button::A)) {
        states_.ChangeState(PlayerState::Ultimate);
    }
    MoveCamera(deltaTime);
}
void Player::LateUpdate(float deltaTime)
{
    Charactor::LateUpdate(deltaTime);
}
//�`��
void Player::Draw()const
{
    Charactor::Draw();
    collider_.Draw();
}

void Player::React(Actor& other)
{

}

void Player::MovePosition(float deltaTime)
{
    GSvector2 input = InputSystem::LeftStick() * 0.1f * deltaTime;

    GSvector3 forward = CameraTransform().forward();
    GSvector3 right = CameraTransform().right();
    // Y�����͖�������XZ���ʂɓ��e
    forward.y = 0;
    right.y = 0;
    forward.normalize();
    right.normalize();

    // ���͂��J���������ɕϊ�
    GSvector3 moveDirection = (forward * input.y) + (right * input.x);
    moveDirection.normalize();
    //����raw���ړ��̋����ɂ���
    float magnitude = input.magnitude();

    GSvector3 moveVector = moveDirection * magnitude * moveSpeed_ * deltaTime;

    //�v���C���[�����炩�ɉ�]
    if (input != GSvector2::zero())
    {
        //�����̕��
        GSquaternion rotation =
            GSquaternion::rotateTowards(
                transform_.rotation(),
                GSquaternion::lookRotation(moveDirection), 15.0f * deltaTime);
        transform_.rotation(rotation);
    }

    // ���s�ړ�����i���[���h��j
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

//���݂̃J�����̕������擾
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

void Player::Debug(float deltaTime)
{
    mesh_->Debug();
}
