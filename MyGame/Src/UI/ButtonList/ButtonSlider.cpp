#include "ButtonSlider.h"
#include "../../GameSystem/InputSystem/InputSystem.h"
#include "../../Sound/SoundManager.h"
#include "../Image.h"
#include "../HorizontalGauge.h"

ButtonSlider::ButtonSlider(GSuint titleTexture, std::function<void(float value)>sliderCallback,float defaultValue, float increment, float min, float max)
    :Button(titleTexture, nullptr), value_{ defaultValue }, increment_{ increment }, valueMin_{ min }, valueMax_{ max },
    sliderCallback_{ sliderCallback },
    //sliderHandle_{ new Image({},Texture::MenuSliderHandle) },
    gauge_{ new HorizontalGauge({},{1,1},Texture::Data(Texture::MenuSliderFill,{0,0.5f}),Texture::Data(Texture::MenuSliderBackGround,{0,0.5f})) }
{
    gauge_->FillAmount(value_ / valueMax_);
    sliderCallback_(value_);
}

ButtonSlider::~ButtonSlider()
{
    //delete sliderHandle_;
    //sliderHandle_ = nullptr;
    delete gauge_;
    gauge_ = nullptr;
}

void ButtonSlider::Update(float deltaTime)
{
    Button::Update(deltaTime);
    if (selected_) volumeSelect();
    GSvector2 volumePos = position_ + GSvector2{ currentAdjust_, kGaugePosAdjust_ };
    gauge_->Position(volumePos);

    volumePos.x += 10 + value_ / valueMax_ * 240;
    //sliderHandle_->Position(volumePos);
}

void ButtonSlider::Draw() const
{
    Button::Draw();
    gauge_->Draw();
    //sliderHandle_->Draw();
}

void ButtonSlider::OnConfirm()
{
}

void ButtonSlider::IsLoakLeft(bool flg)
{
    leftLock_ = flg;
}

void ButtonSlider::IsLoakRight(bool flg)
{
    rightLock_ = flg;
}

float ButtonSlider::FillAmount()
{
    return gauge_->FillAmount();
}

void ButtonSlider::volumeSelect()
{
    int volumeIncrement = 0;
    if (InputSystem::MenuLeft() && !leftLock_)volumeIncrement--;
    if (InputSystem::MenuRight() && !rightLock_)volumeIncrement++;
    //入力がなければ切り替えしない
    if (volumeIncrement == 0)
    {
        impulse_ = false;
        return;
    }
    if (impulse_) return;
    impulse_ = true;
    float prevValue = value_;
    value_ = CLAMP(value_ + increment_ * volumeIncrement, valueMin_, valueMax_);
    gauge_->FillAmount(value_ / valueMax_);

    //上限または下限の時は飛ばす
    if (prevValue == value_)return;
    sliderCallback_(value_);
    SoundManager::PlaySE(Sound::MenuSelect);
}
