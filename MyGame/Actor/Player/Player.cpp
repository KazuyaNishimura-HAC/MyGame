#include "Player.h"
#include <imgui/imgui.h>
#include "../../AssetID/Model.h"
#include "../../World/IWorld.h"
#include "../../GameSystem/InputSystem/InputSystem.h"

Player::Player(IWorld* world, GSuint mesh)
    :Actor(mesh)
{
    world_ = world;
}

Player::Player(IWorld* world, GSuint mesh, const GSvector3& position)
    :Player{ world, mesh }
{
    //èâä˙ç¿ïWê›íË
    transform_.position(position);
}
Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    Actor::Update(deltaTime);
}
void Player::LateUpdate(float deltaTime)
{
    Actor::LateUpdate(deltaTime);
}
//ï`âÊ
void Player::Draw()const
{
    Actor::Draw();
}

void Player::React(Actor& other)
{

}
