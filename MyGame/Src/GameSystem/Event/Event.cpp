#include "Event.h"
#include "../../World/IWorld.h"
#include "../../Actor/Actor.h"
#include "../../Actor/Charactor/Player/Player.h"

Event::Event(IWorld* world,int invokeType, const GSvector3& position, GSvector2 size)
    :world_{ world },invokeType_{ invokeType }, size_{ size }
{
    transform_.position(position);
}

Event::~Event()
{
    world_ = nullptr;
    camera_ = nullptr;
}

bool Event::Invoke()
{
    //終了処理が入ったらreturn
    if(IsEnd()) return false;
    bool invoke;
    switch (invokeType_) {
    case InvokeType::Collision:
        invoke = IsCollide();
        break;
    case InvokeType::Manual:
        invoke = IsInvoke();
        break;
    default:
        return false;
    }
    //発火フラグが発生したら
    if (!invoke) return false;
    isInvoke_ = invoke;
    //イベント開始
    BeginEvent();
    return true;
}

bool Event::IsEnd()
{
    return isEnd_;
}
bool Event::EventWait(float deltaTime)
{
    timer_ += deltaTime;
    return timer_ > eventTime_;
}

bool Event::IsCollide()
{
    Player* player = world_->GetPlayer();
    GSvector3 toPlayerVector = player->Transform().position() - transform_.position();
    toPlayerVector = transform_.inverseTransformVector(toPlayerVector);
    toPlayerVector.x = abs(toPlayerVector.x) - size_.x / 2;
    toPlayerVector.z = abs(toPlayerVector.z) - size_.y / 2;
    bool collidePlayer1 = toPlayerVector.x <= 0 && toPlayerVector.z <= 0;

    //触れたキャラクターを取得
    if (collidePlayer1) reactCharactor_ = player;

    return collidePlayer1;
}

void Event::ResetTimer()
{
    timer_ = 0.0f;
}

void Event::SetEventTime(float time)
{
    eventTime_ = time;
}

void Event::SetInvoke(bool invoke)
{
    isInvoke_ = invoke;
}

bool Event::IsInvoke()
{
    return isInvoke_;
}

void Event::IsDebug()
{
    //GSvector3 pos = transform_.position();
    //glPushMatrix();
    //    glTranslatef(pos.x, pos.y, pos.z); // 原点を移動
    //    glBegin(GL_QUADS);
    //    glVertex3f(0, 0, 0);
    //    glVertex3f(size_.x, 0, 0);
    //    glVertex3f(size_.x, 0, size_.y);
    //    glVertex3f(0, 0, size_.y);
    //    glEnd();
    //glPopMatrix();
}
