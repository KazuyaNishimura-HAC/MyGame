#include "ValueText.h"

ValueText::ValueText(GSvector2 position,GSvector2 size, GScolor color, int value, float align)
    :GUI(position, size, color), value_{ value }
{
    UpdateValue(value, align);
}

void ValueText::Update(float deltaTime)
{
}

void ValueText::Draw() const
{
    if (!enable_)return;
    //fill数値分０を追加
    for (int i = 1; i < fill_ + 1; i++) {
        if (value_ < pow(10, i)) DrawNumber(0, i);
    }

    for (int i = digit_ - 1; i >= 0; i--)
    {
        int number = value_ / (int)powf(10, i);
        number %= (int)powf(10, i + 1);
        DrawNumber(number, i);
    }
}

void ValueText::UpdateValue(int value, float align)
{
    value_ = value;
    if (value == 0)digit_ = 1;
    else digit_ = log10f(value) + 1;
    //左揃え0右揃え1
    align_ = digit_ * (1 - align);
}

void ValueText::DrawNumber(int num, float digit)const
{
    const float constNumberWidth = numbers_.size_.x / 10;
    GSvector2 position = position_;
    position.x -= (digit - align_) * constNumberWidth * size_.x;
    GSrect rect{ num * constNumberWidth,0,(num + 1) * constNumberWidth ,numbers_.size_.y };
    gsDrawSprite2D(numbers_.name_, &position, &rect, NULL, &color_, &size_, 0);
}

void ValueText::NumberFill(int num) {
    fill_ = num;
}

GSuint ValueText::Texture() const
{
    return numbers_.name_;
}
