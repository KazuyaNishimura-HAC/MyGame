#ifndef EVENT_MANAGER_H_
#define EVENT_MANAGER_H_

#include <list>

class Event;

class EventManager
{
public:
    ~EventManager();
    void Update(float deltaTime);
    void Draw()const;
    void Invoke();
    void AddEvent(Event* newEvent);
    void Remove();
    void Clear();
private:
    //イベントリスト
    std::list<Event*> events_;
    //現在行っているイベント
    Event* runningEvent_{ nullptr };
};

#endif
