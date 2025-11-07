#ifndef ULTIMATE_ANIM__EVENT_H_
#define ULTIMATE_ANIM__EVENT_H_
#include "Event.h"

class GUI;
class Player;

class UltimateAnimEvent : public Event
{
public:
    UltimateAnimEvent(IWorld* world,int invokeType, const GSvector3& position = { 0,0,0 }, GSvector2 size = { 1,1 });
    void Update(float deltaTime) override;
    void Draw()const override;
private:
    void BeginEvent()override;
    void EndEvent()override;

    Player* player_{ nullptr };

    float distanceBack = 0.0f;  // プレイヤーの背後に下がる距離
    float distanceSide = 0.0f; //プレイヤーの左右にさがる距離
    float height = 0.0f;  // プレイヤーの上方向の高さ
    float intensity = 0.35f;
};

#endif
