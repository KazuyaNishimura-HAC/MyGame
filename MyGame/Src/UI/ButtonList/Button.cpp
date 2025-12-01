#include "Button.h"

Button::Button(GSuint textureID, std::function<void()> callback , GSvector2 textureSize)
    :texture_{ Texture::Data(textureID)}, callback_{callback}
{
    Size(textureSize);
}

void Button::Update(float deltaTime)
{
    if (!selectMove_) return;
    currentAdjust_ = LERP(0.5f * deltaTime, currentAdjust_, selected_ ? selectAdjust_ : 0);
    alpha_ = LERP(0.5f * deltaTime, alpha_, selected_ ? 1 : 0.5f);
}

void Button::Draw() const
{
    GSvector2 position = position_ + GSvector2{ currentAdjust_, 0 };
    GScolor color{ 1,1,1,alpha_ };
    gsDrawSprite2D(texture_.name_, &position, NULL, NULL, &color, &size_, 0);
}

void Button::SetPosition(GSvector2 position, float selectAdjust)
{
    position_ = position;
    selectAdjust_ = selectAdjust;
}

void Button::OnSelect()
{
    selected_ = true;
}

void Button::OnDeSelect()
{
    selected_ = false;
}

void Button::OnConfirm()
{
    callback_();
}

void Button::SelectMove(bool move)
{
    selectMove_ = move;
}
