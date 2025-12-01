#include "SelectButton.h"
#include "../../GameSystem/InputSystem/InputSystem.h"
#include "../Image.h"
#include "../HorizontalGauge.h"

SelectButton::SelectButton(GSuint titleTexture, GSuint backTexture,GSvector2 size,const GSvector2 offset, std::function<void()> callback, GSvector2 buttonSize)
    :Button(titleTexture, callback, buttonSize),
    frame_{ new Image({-1000,-1000}, backTexture, size) }
{
    frameSize_ = size;
    kFramePosAdjust_ = offset;
}

SelectButton::~SelectButton()
{
    delete frame_;
    frame_ = nullptr;
}

void SelectButton::Update(float deltaTime)
{
    //Button::Update(deltaTime);
    time_ += deltaTime;
    GSvector2 VframeSize;
    if (selected_) {
        VframeSize = { sinf(time_* speed_) * amplitude_,sinf(time_ * speed_) * amplitude_ };
    }
    else {
        time_ = 0.0f;
        //選択してない時は初期設定サイズに戻す
        VframeSize = frameSize_ - frame_->Size();
    }
    GSvector2 frameSize = frame_->Size() + VframeSize;
    GSvector2 framePos = position_ + kFramePosAdjust_;
    frame_->Size(frameSize);
    frame_->Position(framePos);
}

void SelectButton::Draw() const
{
    //ほんとはbuttonにフレーム画像渡したいけど時間内から逆で実装
    frame_->Draw();
    Button::Draw();
}

