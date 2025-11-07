#include "PlayerUI.h"
#include"../Actor/Player/Player.h"
#include "../GameSystem/InputSystem/InputSystem.h"
#include "HorizontalGauge.h"
#include "Texture.h"
PlayerUI::PlayerUI(Player* player,const GSvector2& position)
    :GUI(position)
{
    player_ = player;
    healthGauge_ = new HorizontalGauge(
        GSvector2{ 1500,800 } + position,
        {1,1},
        Texture::Data(Texture::MenuSliderFill, { 0,0 }),
        Texture::Data(Texture::MenuSliderBackGround, { 0,0 })
    );
}

PlayerUI::~PlayerUI()
{
    delete healthGauge_;
    healthGauge_ = nullptr;
}

void PlayerUI::Update(float deltaTime)
{
    float health = (float)player_->GetHealth() / (float)player_->GetMaxHealth();
    healthGauge_->FillAmount(health);
}

void PlayerUI::Draw() const
{
    healthGauge_->Draw();
}
