#ifndef RESULT_UI_H_
#define RESULT_UI_H_
#include "GUI.h"
#include ".././GameSystem/BattleSystem/BattleManager.h"
class IWorld;
class Image;
class ValueText;

class ResultUI : public GUI{
public:
    ResultUI(IWorld* world = nullptr,const GSvector2& position = { 0,0 });
    ~ResultUI();
    void Update(float deltaTime)override;
    void Draw()const override;
    void BeginResult(ResultData data);
    bool IsResult()const;
private:
    void EndResult();
    IWorld* world_{ nullptr };
    Image* rankText_{ nullptr };
    Image* scoreRank_{ nullptr };
    bool isResultOpen_{ false };
    ResultData data_{};
    std::vector<Image*> resultTexts_;
    std::vector<ValueText*> valueTexts_;
    int valuesIndex_[3]{ 0,0,0 };
};

#endif
