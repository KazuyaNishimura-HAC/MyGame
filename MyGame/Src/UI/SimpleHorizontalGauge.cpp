#include "SimpleHorizontalGauge.h"

SimpleHorizontalGauge::SimpleHorizontalGauge(GSvector2 position, GSvector2 size)
    :GUI::GUI(position, size)
{
}

void SimpleHorizontalGauge::Draw() const
{
    if (!enable_)return;
    if (behindCamera_)return;
    //背景
    GSrect bgRect{ position_.x - size_.x / 2, position_.y - size_.y / 2, position_.x + size_.x / 2, position_.y + size_.y / 2 };
    GSvector4 bgCol{ 0.125f, 0.125f, 0.125f, 1 };
    gsDrawRectangle2D(&bgRect, &bgCol);
    //ゲージ
    GSrect fillRect = GSrect(bgRect.left, bgRect.top, bgRect.right, bgRect.bottom);
    fillRect.right = LERP(fillAmount_, fillRect.left, fillRect.right);
    GSvector4 fillCol{ .75f, .75f, .75f, 1 };
    gsDrawRectangle2D(&fillRect, &fillCol);
}

void SimpleHorizontalGauge::FillAmount(float value)
{
    fillAmount_ = value;
}

float SimpleHorizontalGauge::FillAmount()
{
    return fillAmount_;
}

GSrect SimpleHorizontalGauge::FilledRect(float fillAmount)const
{
    GSrect rect{ position_.x - size_.x / 2, position_.y - size_.y / 2, position_.x + size_.x / 2, position_.y + size_.y / 2 };
    rect.right = LERP(fillAmount, rect.left, rect.right);
    return rect;
}


