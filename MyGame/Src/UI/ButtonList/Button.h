#ifndef BUTTON_H_
#define BUTTON_H_

#include "../GUI.h"
#include "../Texture.h"
#include <functional>

class Button :public GUI
{
public:
    Button(GSuint textureID, std::function<void()>callback,GSvector2 textureSize = {1,1});
    virtual void Update(float deltaTime) override;
    virtual void Draw()const override;
    void SetPosition(GSvector2 position, float selectAdjust);
    virtual void OnSelect();
    virtual void OnDeSelect();
    virtual void OnConfirm();
    void SelectMove(bool move);
protected:
    Texture::Data texture_;
    float alpha_{ 1 };
    float selectAdjust_{ 0 }, currentAdjust_{ 0 };
    bool selected_{ false };
    bool selectMove_{ true };
private:
    std::function<void()>callback_;
};

#endif
