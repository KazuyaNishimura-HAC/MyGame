#include "OpenDoorEvent.h"

OpenDoorEvent::OpenDoorEvent(IWorld* world, int invokeType,int eventNum, const GSvector3& position, GSvector2 size)
    :Event::Event(world, invokeType, position, size)
{
    world_ = world;
    eventNumber_ = eventNum;
}

void OpenDoorEvent::Update(float deltaTime)
{
    if (!world_->GetTimeLine().IsRunning()) {
        EndEvent();
    }
}

void OpenDoorEvent::Draw() const
{
}

void OpenDoorEvent::BeginEvent()
{
    std::string eventName = "OpenDoor" + std::to_string(eventNumber_);
    world_->GetTimeLine().StartTimeLine(eventName);
}

void OpenDoorEvent::EndEvent()
{
    SetInvoke(false);
    //一度きりで終了（完全削除）
    isEnd_ = true;
}
