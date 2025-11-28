#ifndef BOSS_BATTLE_START_EVENT_H_
#define BOSS_BATTLE_START_EVENT_H_
#include "Event.h"
class Boss;

class BossBattleStartEvent : public Event
{
public:
    BossBattleStartEvent(IWorld* world,Boss* boss, int invokeType, const GSvector3& position = { 0,0,0 }, GSvector2 size = { 1,1 });
    ~BossBattleStartEvent();
    void Update(float deltaTime) override;
    void Draw()const override;
private:
    void BeginEvent()override;
    void EndEvent()override;
    Boss* boss_{ nullptr };
};

#endif
