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
        position + GSvector2{ Screen::ScreenWidth - 200.0f, 100.0f },
        { 1.5f,1.0f },
        Texture::Data(Texture::HPGaugeFill, { 0.5f,0.5f }),
        Texture::Data(Texture::HPGaugeBG, { 0.5f,0.5f })
    );
    breakGauge_ = new HorizontalGauge(
        position + GSvector2{ Screen::ScreenWidth - 200.0, 100.0f },
        { 1.5f,1.0f },
        Texture::Data(Texture::SkillGaugeFill, { 0.5f,0.5f }),
        Texture::Data(Texture::SkillGaugeBG, { 0.5f,0.5f })
    );
}

BossUI::~BossUI()
{
    delete healthGauge_;
    healthGauge_ = nullptr;
    delete breakGauge_;
    breakGauge_ = nullptr;
}

void BossUI::Update(float deltaTime)
{
    if (boss_->IsBattleMode()) {
        bool flg = boss_->IsBattleMode();
    }
    float healthPt = boss_->GetCurrentHealth() / boss_->GetMaxHealth();
    float breakPt = boss_->CurrentBreakPoint() / boss_->MaxBreakPoint();
    healthGauge_->FillAmount(healthPt);
    //breakGauge_->FillAmount(breakPt);
}

void BossUI::Draw() const
{
    if (!enable_ || !boss_->IsBattleMode()) return;
    healthGauge_->Draw();
    //breakGauge_->Draw();
}
