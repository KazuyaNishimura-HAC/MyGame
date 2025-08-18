#ifndef GAME_END_EVENT
#define GAME_END_EVENT
#include "Event.h"

class GUI;

class GameEndEvent : public Event
{
public:
    GameEndEvent(IWorld* world, const GSvector3& position = { 0,0,0 }, GSvector2 size = { 1,1 });
    void Update(float deltaTime) override;
    void Draw()const override;
    std::vector<GSvector3> cosePath_;
private:
    void BeginEvent()override;
    void EndEvent()override;
    void CameraMove(Camera* camera, int id,float deltaTime);
    void SetCosePath(Charactor* charctor);
    const float countDownTime{ 60 * 3 };
    bool isPlayBGM_{ false };
    bool onceEvents_[2]{ false,false };
    int setImage_{ 0 };
    float cameraAzimuths_[2]{ 0,0 };
    float cameraSpeed_{ 1.25f };
    const GSvector3 k_GoalCamera_{ 0,10,0  };
    std::vector<Camera*> cameras_;
    std::vector<Charactor*> charactors_;
    
};

#endif
