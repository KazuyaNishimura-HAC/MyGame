#include "BossUI.h"
#include"../Actor/Charactor/Enemy/Boss/Boss.h"
#include "../GameSystem/InputSystem/InputSystem.h"
#include "HorizontalGauge.h"
#include "Texture.h"
#include "../World/IWorld.h"
BossUI::BossUI(IWorld* world, Boss* boss, const GSvector2& position)
    :GUI(position)
{
    world_ = world;
    boss_ = boss;
    healthGauge_ = new HorizontalGauge(
        position + GSvector2{Screen::HalfWidth, 100.0f},
        { 3.0f,1.0f },
        Texture::Data(Texture::BossSliderFill, { 0.5f,0.5f }),
        Texture::Data(Texture::BossMenuSliderBG, { 0.5f,0.5f })
    );
}

BossUI::~BossUI()
{
    delete healthGauge_;
    healthGauge_ = nullptr;
}

void BossUI::Update(float deltaTime)
{
    if (boss_->IsBattleMode()) {
        bool flg = boss_->IsBattleMode();
    }
    float health = boss_->GetCurrentHealth() / boss_->GetMaxHealth();
    healthGauge_->FillAmount(health);
}

void BossUI::Draw() const
{
    if (!enable_ || !boss_->IsBattleMode()) return;
    healthGauge_->Draw();
}
