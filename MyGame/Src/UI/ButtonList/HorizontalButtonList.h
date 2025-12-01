#ifndef HORIZONTAL_BUTTON_LIST_H_
#define HORIZONTAL_BUTTON_LIST_H_

#include "../GUI.h"
#include <vector>

class Button;

//ボタンを横選択してるように見せるクラス
class HorizontalButtonList :public GUI
{
public:
    HorizontalButtonList(GSvector2 position, int defalutIndex = 0, float buttonDistance = 60);
    ~HorizontalButtonList()override;
    void AddButton(Button* newButton,GSvector2 offset = { 0.0f,0.0f });
    virtual void Update(float deltaTime) override;
    virtual void Draw()const override;
    void Enable(bool enable)override;
    int SelectIndex();
private:
    void Select();
    void Confirm();
    int currentIndex_ = 0;
    int defaultIndex_;
    bool impulse_ = false;
    std::vector<Button*>buttons_;
    float buttonDistance_{ 72 };

    bool enabledFrameWait_{ false };
};

#endif
