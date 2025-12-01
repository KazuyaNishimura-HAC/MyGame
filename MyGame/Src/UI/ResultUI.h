#ifndef RESULT_UI_H_
#define RESULT_UI_H_
#include "GUI.h"
class IWorld;
class Image;
class ResultUI : public GUI{
public:
    ResultUI(IWorld* world = nullptr,const GSvector2& position = { 0,0 });
    ~ResultUI();
    void Update(float deltaTime)override;
    void Draw()const override;
    void BeginResult();
private:
    void EndResult();
    IWorld* world_{ nullptr };
    Image* resultText_{ nullptr };
    Image* scoreRank_{ nullptr };
};

#endif
