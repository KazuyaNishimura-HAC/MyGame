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
    //‰ŠúÀ•WÝ’è
    transform_.position(position);

}
Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    Actor::Update(deltaTime);
    mesh_->Debug();
}
void Player::LateUpdate(float deltaTime)
{
    Actor::LateUpdate(deltaTime);
}
//•`‰æ
void Player::Draw()const
{
    Actor::Draw();
}

void Player::React(Actor& other)
{

}
