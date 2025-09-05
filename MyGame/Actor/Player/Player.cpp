#include "Player.h"
#include <imgui/imgui.h>
#include "../../AssetID/Model.h"
#include "../../World/IWorld.h"
#include "../../GameSystem/InputSystem/InputSystem.h"

//�X�e�[�g�w�b�_�[
#include "State/PlayerState.h"
#include "State/PlayerIdle.h"
#include "State/PlayerMove.h"

Player::Player(IWorld* world, GSuint mesh)
    :Actor(mesh)
{
    world_ = world;
    //�X�e�[�g�̒ǉ�
    states_.AddState(PlayerState::Idle, new PlayerIdle(this));
    states_.AddState(PlayerState::Move, new PlayerMove(this));
    states_.ChangeState(PlayerState::Move);

    camera_ = new CameraController(CameraController::Player);
    world_->AddCameraController(camera_);
    camera_->SetSmooth(true);
}

Player::Player(IWorld* world, GSuint mesh, const GSvector3& position)
    :Player{ world, mesh }
{
    //�������W�ݒ�
    transform_.position(position);
}
Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    Actor::Update(deltaTime);
    states_.Update(deltaTime);
}
void Player::LateUpdate(float deltaTime)
{
    Actor::LateUpdate(deltaTime);
}
//�`��
void Player::Draw()const
{
    Actor::Draw();
}

void Player::React(Actor& other)
{

}

void Player::Debug(float deltaTime)
{
    mesh_->Debug();
    if(InputSystem::ButtonTrigger(InputSystem::Button::A)) states_.ChangeState(PlayerState::PlayerState::Idle);
    if (InputSystem::ButtonTrigger(InputSystem::Button::B)) states_.ChangeState(PlayerState::PlayerState::Move);
}
