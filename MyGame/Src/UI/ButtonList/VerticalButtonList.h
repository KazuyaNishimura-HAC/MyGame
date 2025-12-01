#ifndef VERTICAL_BUTTON_LIST_H_
#define VERTICAL_BUTTON_LIST_H_

#include "../GUI.h"
#include <vector>

class Button;

//ボタンを縦選択してるように見せるクラス
class VerticalButtonList :public GUI
{
public:
    VerticalButtonList(GSvector2 position, int defalutIndex = 0, float buttonDistance = 60);
    ~VerticalButtonList()override;
    void AddButton(Button* newButton,bool def = true);
    void SelectBG(GSuint textureID, GSvector2 size, GSvector2 offset = {0,0});
    virtual void Update(float deltaTime) override;
    virtual void Draw()const override;
    void Enable(bool enable)override;
    int SelectIndex();
    void LeftSliderLock(bool flg);
    void RightSliderLock(bool flg);
    float FillAmouts();
private:
    void Select();
    void Confirm();
    int currentIndex_ = 0;
    int defaultIndex_;
    bool impulse_ = false;
    std::vector<Button*>buttons_;
    float buttonDistance_{ 72 };
    GUI* selectBuck_{ nullptr };
    bool enabledFrameWait_{ false };
    GSvector2 bgOffset_{};
};

#endif
