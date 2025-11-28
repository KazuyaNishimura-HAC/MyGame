#ifndef EVENT_MANAGER_H_
#define EVENT_MANAGER_H_

#include <list>
#include "TimeLine/TimeLine.h"

class Event;

class EventManager
{
public:
    EventManager();
    ~EventManager();
    void Update(float deltaTime);
    void Draw()const;
    void Invoke();
    void AddEvent(Event* newEvent);
    void Remove();
    void Clear();
    void Debug();
    bool IsRunning();
    TimeLine& GetTimeLine();
    // コピー禁止
    EventManager(const EventManager& other) = delete;
    EventManager& operator=(const EventManager& other) = delete;
private:
    //イベントリスト
    std::list<Event*> events_;
    //現在行っているイベント
    Event* runningEvent_{ nullptr };
    //タイムラインイベント
    TimeLine timeLine_;
    
};

#endif
