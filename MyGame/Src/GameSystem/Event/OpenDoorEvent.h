#ifndef OPEN_DOOR_EVENT_H_
#define OPEN_DOOR_EVENT_H_
#include "Event.h"

class GUI;

class OpenDoorEvent : public Event
{
public:
    OpenDoorEvent(IWorld* world, int invokeType, int eventNum = 0, const GSvector3& position = { 0,0,0 }, GSvector2 size = { 1,1 });
    void Update(float deltaTime) override;
    void Draw()const override;
private:
    void BeginEvent()override;
    void EndEvent()override;

    Player* player_{ nullptr };
    int eventNumber_{ 0 };
};

#endif
