#include "OpenDoorEvent.h"
#include "../../World/IWorld.h"
#include "../../GameSystem/Event/TimeLine/TimeLine.h"
#include "../../Actor/Actor.h"
#include "../Field/Field.h"
#include "../../Actor/Model.h"

OpenDoorEvent::OpenDoorEvent(IWorld* world, int invokeType,int eventNum, const GSvector3& position, GSvector2 size)
    :Event::Event(world, invokeType, position, size)
{
    world_ = world;
    eventNumber_ = eventNum;
    GSvector3 doorOffset1 = { 0,0,-1.6f };
    GSvector3 doorOffset2 = { 0,0,1.6f };
    doors_.push_back(new Actor(Model::Door,position + doorOffset1,{ 0,180,0 }));
    doors_.push_back(new Actor(Model::Door, position + doorOffset2));
    for (auto door : doors_) {
        door->SetEnable(false);
        world_->AddActor(door);
    }

    barrier_ = new Field(position, { 1,3,2 });
    world_->AddField(barrier_);
}

void OpenDoorEvent::Update(float deltaTime)
{
    if (waitTimer_ > 0.0f) {
        waitTimer_ -= deltaTime / 60.0f;
        return;
    }
    for (size_t i = 0; i < doors_.size();++i) {
        int velocity = 0;
        if (i == 0) velocity = 1;
        else velocity = -1;
        doors_[i]->Transform().rotate({0,rotateSpeed_ * velocity * deltaTime,0});
    }
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
    barrier_->Die();
    //一度きりで終了（完全削除）
    isEnd_ = true;
}
