#ifndef PLAYER_UI_H_
#define PLAYER_UI_H_
#include "GUI.h"
class HorizontalGauge;
class Player;

class PlayerUI : public GUI{
public:
    PlayerUI(IWorld* world, Player* player,const GSvector2& position = { 0,0 });
    ~PlayerUI();
    void Update(float deltaTime)override;
    void Draw()const override;
private:
    void UpdateHealthGauge();
    void UpdateSkillGauge();
    void UpdateGuardGauge();
    IWorld* world_{ nullptr };
    HorizontalGauge* healthGauge_{ nullptr };
    HorizontalGauge* skillGauge_{ nullptr };
    HorizontalGauge* guardBreakGauge_{ nullptr };
    Player* player_{ nullptr };
};
#endif
