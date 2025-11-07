#ifndef HORIZONTAL_GAUGE_H_
#define HORIZONTAL_GAUGE_H_

#include "SimpleHorizontalGauge.h"
#include "Texture.h"

class HorizontalGauge :public SimpleHorizontalGauge
{
public:
    HorizontalGauge(GSvector2 position, GSvector2 size, GSuint gauge, GSuint backGround, float fillAlign = 0);
    HorizontalGauge(GSvector2 position, GSvector2 size, Texture::Data gauge, Texture::Data backGround, float fillAlign = 0);
    virtual void Update(float deltaTime) override {}
    virtual void Draw()const override;
protected:
    void DrawGauge(Texture::Data texture, float fillAmount = 1)const;
    float fillAlign_;
    Texture::Data fill_, backGround_;
};

#endif
