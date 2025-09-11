#ifndef EVENT_H_
#define EVENT_H_

#include <gslib.h>
#include <GStransform.h>
#include "../../World/World.h"

class IWorld;
class CameraController;

//接触か任意か
struct InvokeType {
    enum Type {
        Collision,
        Manual
    };
};
class Event
{
public:
    Event(IWorld* world,int invokeType,const GSvector3& position = { 0, 0, 0 },GSvector2 size = { 1, 1 });
    virtual ~Event();
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() const {};
    virtual bool Invoke();
    void SetInvoke(bool invoke);
    bool IsInvoke();
    bool IsEnd();
protected:
    virtual void BeginEvent() = 0;
    virtual void EndEvent() = 0;
    bool EventWait(float deltaTime);
    bool IsCollide();
    void ResetTimer();
    void SetEventTime(float time);
    void IsDebug();
    IWorld* world_{ nullptr };
    GStransform transform_;
    CameraController* camera_{ nullptr };
    GSvector2 size_{ 1,1 };
    //衝突したキャラクター
    Actor* reactCharactor_{ nullptr };
    float timer_{ 0 };
    float eventTime_{ 0 };
    int sequence_{ 0 };
    int invokeType_;
    bool isInvoke_{ false };
    bool isEnd_{ false };
};

#endif
