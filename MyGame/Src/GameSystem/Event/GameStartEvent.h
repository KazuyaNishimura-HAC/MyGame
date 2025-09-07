#ifndef GAME_START_EVENT
#define GAME_START_EVENT

#include "Event.h"
#include "../../UI/BlinkingImage.h"
#include <vector>
class GUI;

class GameStartEvent : public Event
{
public:
    GameStartEvent(IWorld* world, const GSvector3& position = {0,0,0},GSvector2 size = {1,1});
    void Update(float deltaTime) override;
    void Draw()const override;
private:
    void BeginEvent()override;
    void EndEvent()override;

    //操作説明UI表示
    void GuideUI();
    std::vector<GUI*> countDown_;
    BlinkingImage* controllerGuide_;
    float countDownTime{ 60 };
    int setImage_{ 0 };
};

#endif
