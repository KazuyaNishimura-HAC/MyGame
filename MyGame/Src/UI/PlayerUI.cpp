#include "PlayerUI.h"
#include"../Actor/Charactor/Player/Player.h"
#include "../GameSystem/InputSystem/InputSystem.h"
#include "HorizontalGauge.h"
#include "Texture.h"
#include "Image.h"
#include "ValueText.h"
#include "../World/IWorld.h"
PlayerUI::PlayerUI(IWorld* world, Player* player,const GSvector2& position)
    :GUI(position)
{
    world_ = world;
    player_ = player;
    healthGauge_ = new HorizontalGauge(
        GSvector2{ 100,50 } + position,
        { 1.5f,1 },
        Texture::Data(Texture::HPGaugeFill, { 0,0 }),
        Texture::Data(Texture::HPGaugeBG, { 0,0 })
    );
    skillGauge_ = new HorizontalGauge(
        GSvector2{ 197,70 } + position,
        { 1.5f,1 },
        Texture::Data(Texture::SkillGaugeFill, { 0,0 }),
        Texture::Data(Texture::SkillGaugeBG, { 0,0 })
    );
    guardBreakGauge_ = new HorizontalGauge(
        position,
        { 0.3f,0.3f },
        Texture::Data(Texture::MenuSliderFill, { 0.5f,0.5f }),
        Texture::Data(Texture::MenuSliderBackGround, { 0.5f,0.5f })
    );
    ultIcon_ = new Image({1700,900},Texture::UltimateIconBG,{ 0.5f,0.5f });

    comboText_ = new ValueText({ 100,200 }, { 0.25f,0.25f });
    hitText_ = new Image({ 280,250 }, Texture::HitText, { 0.25f,0.25f });
}

PlayerUI::~PlayerUI()
{
    delete healthGauge_;
    healthGauge_ = nullptr;
    delete skillGauge_;
    skillGauge_ = nullptr;
    delete guardBreakGauge_;
    guardBreakGauge_ = nullptr;
    delete ultIcon_;
    ultIcon_ = nullptr;
    delete comboText_;
    comboText_ = nullptr;
    delete hitText_;
    hitText_ = nullptr;
}

void PlayerUI::Update(float deltaTime)
{
    if (!enable_) return;
    UpdateHealthGauge();
    UpdateSkillGauge();
    UpdateGuardGauge();
    ultIcon_->Update(deltaTime);
    comboText_->UpdateValue(player_->GetCurrentCombo());
    hitText_->Update(deltaTime);
}

void PlayerUI::Draw() const
{
    if (!enable_) return;
    healthGauge_->Draw();
    skillGauge_->Draw();
    if(player_->IsDrawGuardBreakUI()) guardBreakGauge_->Draw();
    //ultIcon_->Draw();
    if (player_->GetCurrentCombo() != 0) {
        comboText_->Draw();
        hitText_->Draw();
    }
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
