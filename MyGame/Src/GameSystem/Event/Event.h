#ifndef EVENT_H_
#define EVENT_H_

#include <gslib.h>
#include <GStransform.h>
#include "../../World/World.h"

class IWorld;

class Event
{
public:
    Event(IWorld* world,const GSvector3& position = { 0, 0, 0 },GSvector2 size = { 1, 1 });
    virtual ~Event();
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() const {};
    virtual bool Collide();
    bool IsEnd();
protected:
    virtual void BeginEvent() = 0;
    virtual void EndEvent() = 0;
    bool EventWait(float deltaTime);
    bool IsCollide();
    void IsDebug();
    IWorld* world_{ nullptr };
    GStransform transform_;
    GSvector2 size_{ 1,1 };
    //衝突したキャラクター
    Actor* reactCharactor_{ nullptr };
    float timer_{ 0 };
    int sequence_{ 0 };

    bool isActive_{ false }, isEnd_{ false };
};

#endif
