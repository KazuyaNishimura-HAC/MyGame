#ifndef SELECT_BUTTON_H_
#define SELECT_BUTTON_H_

#include "Button.h"

class SelectButton : public Button
{
public:
    SelectButton(GSuint titleTexture, GSuint backTexture, GSvector2 size = { 1,1 }, const GSvector2 offset = { 0,0 }, std::function<void()> callback = nullptr, GSvector2 buttonSize = {1,1});
    ~SelectButton()override;
    void Update(float deltaTime) override;
    virtual void Draw()const override;
private:
    GUI* frame_;
    bool impulse_{ false };
    GSvector2 kFramePosAdjust_;
    float time_{ 0 };
    float amplitude_{ 0.005f };
    float speed_{ 0.1f };
    GSvector2 frameSize_;

};
#endif
