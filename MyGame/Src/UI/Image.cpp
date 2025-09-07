#include "Image.h"

Image::Image(GSvector2 position, GSuint textureID, GSvector2 scale)
    :Image(position, Texture::Data(textureID), scale)
{
}

Image::Image(GSvector2 position, Texture::Data data, GSvector2 scale)
    : GUI(position, scale), texture_{ data }
{
}

void Image::Draw() const
{
    if (!enable_)return;
    GSvector2 center = texture_.size_ * texture_.centerAlign_;
    gsDrawSprite2D(texture_.name_, &position_, NULL, &center, &color_, &size_, 0);
}

GSuint Image::Texture() const
{
    return texture_.name_;
}

void Image::Texture(Texture::Data data)
{
    texture_ = data;
}
