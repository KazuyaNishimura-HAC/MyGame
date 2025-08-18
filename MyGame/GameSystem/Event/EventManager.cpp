#include "EventManager.h"
#include "Event.h"
#include "../../World/IWorld.h"

EventManager::~EventManager()
{
    Clear();
}

void EventManager::Update(float deltaTime)
{
    //イベントが開始したらUpdate処理
    if (runningEvent_ == nullptr)return;

    runningEvent_->Update(deltaTime);
    if (runningEvent_->IsEnd())runningEvent_ = nullptr;
}

void EventManager::Draw() const
{
    
    for (auto ev : events_)
    {
        if (ev == nullptr)continue;
        ev->Draw();
    }
}

void EventManager::Collide()
{
    //イベントの重複処理禁止
    if (runningEvent_ != nullptr)return;
    for (auto ev : events_)
    {
        if (!ev->Collide())continue;
        runningEvent_ = ev;
        break;
    }
}

void EventManager::AddEvent(Event* newEvent)
{
    events_.push_back(newEvent);
}

void EventManager::Remove()
{
    for (auto i = events_.begin(); i != events_.end();)
    {
        if ((*i)->IsEnd())
        {
            delete* i;
            i = events_.erase(i);
        }
        else ++i;
    }
}

void EventManager::Clear()
{
    runningEvent_ = nullptr;
    for (auto ev : events_)
    {
        delete ev;
    }
    events_.clear();
}
