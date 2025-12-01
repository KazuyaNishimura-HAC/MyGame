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
    guardBreakGauge_ = new HorizontalGauge(
        position,
        { 0.3f,0.3f },
        Texture::Data(Texture::MenuSliderFill, { 0.5f,0.5f }),
        Texture::Data(Texture::MenuSliderBackGround, { 0.5f,0.5f })
    );
}

PlayerUI::~PlayerUI()
{
    delete healthGauge_;
    healthGauge_ = nullptr;
    delete skillGauge_;
    skillGauge_ = nullptr;
    delete guardBreakGauge_;
    guardBreakGauge_ = nullptr;
}

void PlayerUI::Update(float deltaTime)
{
    UpdateHealthGauge();
    UpdateSkillGauge();
    UpdateGuardGauge();
}

void PlayerUI::Draw() const
{
    if (!enable_) return;
    healthGauge_->Draw();
    skillGauge_->Draw();
    if(player_->IsDrawGuardBreakUI()) guardBreakGauge_->Draw();
    
}

void PlayerUI::UpdateHealthGauge()
{
    float health = player_->GetCurrentHealth() / player_->GetMaxHealth();
    healthGauge_->FillAmount(health);
}

void PlayerUI::UpdateSkillGauge()
{
    float skill = player_->CurrentSkillPoint() / player_->MaxSkillPoint();
    skillGauge_->FillAmount(skill);
}

void PlayerUI::UpdateGuardGauge()
{
    float guard = player_->CurrentGuardPoint() / player_->MaxGuardPoint();
    guardBreakGauge_->FillAmount(guard);
    //ゲージ描画座標をプレイヤー中心にする
    GSvector3 gaugePos = player_->Transform().position() + GSvector3{ 0,1,0 };
    guardBreakGauge_->Transform(&gaugePos);
    if (healthGauge_->IsbehindCamera()) guardBreakGauge_->Enable(false);
    else guardBreakGauge_->Enable(true);
}
