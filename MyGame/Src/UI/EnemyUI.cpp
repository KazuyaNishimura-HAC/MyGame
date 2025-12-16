#include "EnemyUI.h"
#include"../Actor/Charactor/Enemy/Enemy.h"
#include "../GameSystem/InputSystem/InputSystem.h"
#include "HorizontalGauge.h"
#include "Texture.h"
#include "../World/IWorld.h"
EnemyUI::EnemyUI(IWorld* world, Enemy* enemy, const GSvector2& position)
    :GUI(position)
{
    world_ = world;
    enemy_ = enemy;
    healthGauge_ = new HorizontalGauge(
        position,
        { 0.5f,0.5f },
        Texture::Data(Texture::HPGaugeFill, { 0.5f,0.5f }),
        Texture::Data(Texture::HPGaugeBG, { 0.5f,0.5f })
    );
    breakGauge_ = new HorizontalGauge(
        position,
        { 0.5f,0.5f },
        Texture::Data(Texture::SkillGaugeFill, { 0.5f,0.5f }),
        Texture::Data(Texture::SkillGaugeBG, { 0.5f,0.5f })
    );
}

EnemyUI::~EnemyUI()
{
    delete healthGauge_;
    healthGauge_ = nullptr;
    delete breakGauge_;
    breakGauge_ = nullptr;
}

void EnemyUI::Update(float deltaTime)
{
    float healthPt = enemy_->GetCurrentHealth() / enemy_->GetMaxHealth();
    float breakPt = enemy_->CurrentBreakPoint() / enemy_->MaxBreakPoint();
    healthGauge_->FillAmount(healthPt);
    breakGauge_->FillAmount(breakPt);
    GSvector3 gaugePos = enemy_->Transform().position() + GSvector3{ 0,2,0 };
    
    //スクリーン描画をするか
    if (isScreenPos_) {
        healthGauge_->Transform(&gaugePos);
        GSvector2 breakGaugePos = breakGauge_->ScreenPosition(&gaugePos) + breakGaugeOffset_;
        breakGauge_->Position(breakGaugePos);
        if (healthGauge_->IsbehindCamera()) {
            healthGauge_->Enable(false);
            breakGauge_->Enable(false);
        }
        else {
            healthGauge_->Enable(true);
            breakGauge_->Enable(true);
        }
    }
}

void EnemyUI::Draw() const
{
    if (!enable_ || !enemy_->IsBattleMode()) return;
    healthGauge_->Draw();
    breakGauge_->Draw();
}
