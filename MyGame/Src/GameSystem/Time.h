#ifndef TIME_H_
#define TIME_H_

#include <GSmath.h>

struct TimeScale
{
public:
    /// <summary>
    /// 
    /// </summary>
    /// <param name="timeScale">呼び出し時タイムスケール</param>
    /// <param name="affectTime">何秒かけて補間するか</param>
    /// <param name="isAffectRealTime">リアルタイムか</param>
    /// <param name="targetTimeScale">目標タイムスケール</param>
    TimeScale(float timeScale, float affectTime, bool isAffectRealTime = false, float targetTimeScale = 1)
        :timeScale_{ timeScale }, startTimeScale_{ timeScale }, targetTimeScale_{ targetTimeScale }, affectTime_{ affectTime * 60 }, affectStart_{ affectTime * 60 + 1 }, isAffectRealTime_{ isAffectRealTime } {};
    TimeScale(float timeScale = 1)
        :timeScale_{ timeScale }, startTimeScale_{ timeScale }, targetTimeScale_{ timeScale } {};
    void Update(float deltaTime)
    {
        deltaTime *= isAffectRealTime_ ? 1 : timeScale_;
        affectTime_ = MAX(affectTime_ - deltaTime, 0);
        timeScale_ = LERP(affectTime_ / affectStart_, targetTimeScale_, startTimeScale_);
    }
    bool IsTimeScaleDefault() { return timeScale_ == 1 ; }
    float timeScale_ = 1;
private:
    float affectTime_ = 0;
    float affectStart_ = 1;
    bool isAffectRealTime_ = false;
    float startTimeScale_ = 1;
    float targetTimeScale_ = 1;
};
class Time
{
public:
    void Update(float deltaTime)
    {
        deltaTime_ = deltaTime;
        if (pause_)return;
        timeScale_.Update(deltaTime);
    }
    float DeltaTime() { return deltaTime_; }
    float ScaledDeltaTime() { return deltaTime_ * timeScale_.timeScale_; }
    float GameDeltaTime() { return ScaledDeltaTime() * (pause_ ? 0 : 1); }
    void SetTimeScale(TimeScale timeScale) { timeScale_ = timeScale; }
    float GetTimeScale() { return timeScale_.timeScale_; }
    void SetPause(bool pause) { pause_ = pause; }
    bool IsPause() { return pause_; }
    bool IsTimeScaleDefault() { return timeScale_.timeScale_ == 1; }
private:
    float deltaTime_{ 0.0f };
    bool pause_{ false };
    TimeScale timeScale_;
};

#endif
