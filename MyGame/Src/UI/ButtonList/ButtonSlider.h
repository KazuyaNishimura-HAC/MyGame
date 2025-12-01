#ifndef BUTTON_SLIDER_H_
#define BUTTON_SLIDER_H_

#include "Button.h"
class HorizontalGauge;

class ButtonSlider : public Button
{
public:
    ButtonSlider(GSuint titleTexture, std::function<void(float value)>sliderCallback,
        float defaultValue, float increment, float min, float max);
    ~ButtonSlider()override;
    void Update(float deltaTime) override;
    virtual void Draw()const override;
    void OnConfirm() override;
    void IsLoakLeft(bool flg);
    void IsLoakRight(bool flg);
    float FillAmount();
private:
    void volumeSelect();
    HorizontalGauge* gauge_;
    //GUI* sliderHandle_;
    std::function<void(float value)>sliderCallback_;
    float value_, valueMin_, valueMax_, increment_;
    bool impulse_{ false };
    const float kGaugePosAdjust_ = 76;
    bool leftLock_{ false };
    bool rightLock_{ false };
};
#endif
