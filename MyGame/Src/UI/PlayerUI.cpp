#include "PlayerUI.h"
#include"../Actor/Charactor/Player/Player.h"
#include "../GameSystem/InputSystem/InputSystem.h"
#include "HorizontalGauge.h"
#include "Texture.h"
#include "../World/IWorld.h"
PlayerUI::PlayerUI(IWorld* world, Player* player,const GSvector2& position)
    :GUI(position)
{
    world_ = world;
    player_ = player;
    healthGauge_ = new HorizontalGauge(
        GSvector2{ 1500,800 } + position,
        { 1,1 },
        Texture::Data(Texture::MenuSliderFill, { 0,0 }),
        Texture::Data(Texture::MenuSliderBackGround, { 0,0 })
    );
    skillGauge_ = new HorizontalGauge(
        GSvector2{ 1500,900 } + position,
        { 1,1 },
        Texture::Data(Texture::MenuSliderFill, { 0,0 }),
        Texture::Data(Texture::MenuSliderBackGround, { 0,0 })
    );
}

PlayerUI::~PlayerUI()
{
    delete healthGauge_;
    healthGauge_ = nullptr;
    delete skillGauge_;
    skillGauge_ = nullptr;
}

void PlayerUI::Update(float deltaTime)
{
    float health = player_->GetCurrentHealth() / player_->GetMaxHealth();
    float skill = player_->CurrentSkillPoint() / player_->MaxSkillPoint();
    healthGauge_->FillAmount(health);
    skillGauge_->FillAmount(skill);
}

void PlayerUI::Draw() const
{
    if (!enable_) return;
    healthGauge_->Draw();
    skillGauge_->Draw();
}
