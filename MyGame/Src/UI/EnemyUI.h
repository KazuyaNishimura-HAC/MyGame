#ifndef ENEMY_UI_H_
#define ENEMY_UI_H_
#include "GUI.h"
class HorizontalGauge;
class Enemy;

class EnemyUI : public GUI {
public:
    EnemyUI(IWorld* world, Enemy* enemy, const GSvector2& position = { 0,0 });
    ~EnemyUI();
    void Update(float deltaTime)override;
    void Draw()const override;
private:
    IWorld* world_{ nullptr };
    HorizontalGauge* healthGauge_{ nullptr };
    HorizontalGauge* breakGauge_{ nullptr };
    Enemy* enemy_{ nullptr };
    GSvector2 breakGaugeOffset_{ 15,6 };
    bool isScreenPos_{ true };
};
#endif
