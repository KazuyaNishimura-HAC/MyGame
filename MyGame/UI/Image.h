#ifndef IMAGE_H_
#define IMAGE_H_

#include "GUI.h"
#include "Texture.h"

class Image :public GUI
{
public:
    Image(GSvector2 position, GSuint textureID, GSvector2 scale = { 1,1 });
    Image(GSvector2 position, Texture::Data data, GSvector2 scale = { 1,1 });
    virtual void Draw()const override;
    virtual GSuint Texture()const override;
    void Texture(Texture::Data data);
protected:
    Texture::Data texture_;
};

#endif
