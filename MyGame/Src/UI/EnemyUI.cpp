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
        Texture::Data(Texture::MenuSliderFill, { 0.5f,0.5f }),
        Texture::Data(Texture::MenuSliderBackGround, { 0.5f,0.5f })
    );
}

EnemyUI::~EnemyUI()
{
    delete healthGauge_;
    healthGauge_ = nullptr;
}

void EnemyUI::Update(float deltaTime)
{
    float health = enemy_->GetCurrentHealth() / enemy_->GetMaxHealth();
    healthGauge_->FillAmount(health);
    GSvector3 gaugePos = enemy_->Transform().position() + GSvector3{ 0,2,0 };
    if(isScreenPos) healthGauge_->Transform(&gaugePos);
    if (healthGauge_->IsbehindCamera()) healthGauge_->Enable(false);
    else healthGauge_->Enable(true);
}

void EnemyUI::Draw() const
{
    if (!enable_ || !enemy_->IsBattleMode()) return;
    healthGauge_->Draw();
}
