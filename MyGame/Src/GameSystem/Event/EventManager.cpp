#include "EventManager.h"
#include "Event.h"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
    Clear();
}

void EventManager::Update(float deltaTime)
{
    
    //イベントが開始したらUpdate処理
    if (runningEvent_) {
        runningEvent_->Update(deltaTime);
        if (!runningEvent_->IsInvoke() || runningEvent_->IsEnd()) runningEvent_ = nullptr;
    }
    timeLine_.Update(deltaTime);
}

void EventManager::Draw() const
{
    for (auto ev : events_)
    {
        if (ev == nullptr)continue;
        ev->Draw();
    }
}

void EventManager::Invoke()
{
    //イベントの重複処理禁止
    if (runningEvent_)return;
    for (auto ev : events_)
    {
        if (!ev->Invoke())continue;
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
    timeLine_.AllClear();
}

void EventManager::Debug()
{
}

bool EventManager::IsRunning()
{
    return runningEvent_ != nullptr;
}

TimeLine& EventManager::GetTimeLine()
{
    return timeLine_;
}
