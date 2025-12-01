#ifndef BOSS_UI_H_
#define BOSS_UI_H_
#include "GUI.h"
class HorizontalGauge;
class Boss;

class BossUI : public GUI {
public:
    BossUI(IWorld* world, Boss* boss, const GSvector2& position = { 0,0 });
    ~BossUI();
    void Update(float deltaTime)override;
    void Draw()const override;
private:
    IWorld* world_{ nullptr };
    HorizontalGauge* healthGauge_{ nullptr };
    Boss* boss_{ nullptr };
};
#endif
