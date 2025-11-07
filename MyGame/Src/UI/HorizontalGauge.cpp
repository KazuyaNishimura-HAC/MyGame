#include "HorizontalGauge.h"

HorizontalGauge::HorizontalGauge(GSvector2 position, GSvector2 size, GSuint gauge, GSuint backGround, float fillAlign)
    :HorizontalGauge(position, size, Texture::Data(gauge), Texture::Data(backGround), fillAlign)
{
}

HorizontalGauge::HorizontalGauge(GSvector2 position, GSvector2 size, Texture::Data gauge, Texture::Data backGround, float fillAlign)
    :SimpleHorizontalGauge(position, size), fill_{ gauge }, backGround_{ backGround }, fillAlign_{ fillAlign }
{
}

void HorizontalGauge::Draw() const
{
    if (!enable_)return;
    DrawGauge(backGround_);
    DrawGauge(fill_, fillAmount_);
}

void HorizontalGauge::DrawGauge(Texture::Data texture, float fillAmount) const
{
    GSvector2 position = position_;
    position.x += texture.size_.x * fillAlign_ * (1 - fillAmount);
    GSrect rect = fillAlign_ == 0 ?
        GSrect{ 0, 0, texture.size_.x * fillAmount, texture.size_.y } :
        GSrect{ texture.size_.x * (1 - fillAmount), 0, texture.size_.x, texture.size_.y };
    GSvector2 center = texture.size_ * texture.centerAlign_;
    gsDrawSprite2D(texture.name_, &position, &rect, &center, &color_, &size_, 0);
}
