#ifndef SIMPLE_HORIZONTAL_GAUGE_H_
#define SIMPLE_HORIZONTAL_GAUGE_H_

#include "GUI.h"

class SimpleHorizontalGauge :public GUI
{
public:
    SimpleHorizontalGauge(GSvector2 position, GSvector2 size);
    virtual void Update(float deltaTime) override {}
    virtual void Draw()const override;
    virtual void FillAmount(float value);
    float FillAmount();
protected:
    float fillAmount_{ 1 };
private:
    GSrect FilledRect(float fillAmount)const;
};

#endif
