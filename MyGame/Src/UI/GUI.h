#ifndef GUI_H_
#define GUI_H_

#include <gslib.h>
#include "../Screen.h"
#include "../GameSystem/Camera/Camera.h"

class GUI
{
public:
    GUI(GSvector2 position = GSvector2::zero(), GSvector2 size = GSvector2::one(), GScolor color = GScolor(1, 1, 1, 1)) :position_{ position }, size_{ size }, color_{ color } {};
    virtual ~GUI() {};
    virtual void Update(float deltaTime) {};
    virtual void Draw()const
    {
        if (!enable_)return;
        gsDrawRectangle2D(new GSrect(position_.x - size_.x / 2, position_.y - size_.y / 2, position_.x + size_.x / 2, position_.y + size_.y / 2), new GSvector4(0, 1, 0, 1));
    };
    //3D空間からUIに座標変換
    virtual GSvector2 ScreenPosition(const GSvector3* worldPosition)
    {
        GSvector3 position;
        Screen::CalculateScreenPosition(&position, worldPosition);
        behindCamera_ = position.z > 1;
        return { position.x,position.y };
    }
    virtual void Transform(const GSvector3* worldPosition)
    {
        position_ = ScreenPosition(worldPosition);
    }
    virtual void Position(const GSvector2& position)
    {
        position_ = position;
    }
    GSvector2 Position()const { return position_; }
    virtual void Enable(bool enable) { enable_ = enable; }
    virtual bool Enable() { return enable_; }
    bool TimeScaled()const { return timeScaled_; }
    bool end_{ false };
    void End() { end_ = true; };
    void Color(GScolor color) { color_ = color; }
    GScolor Color()const { return color_; }
    void Size(GSvector2 size) { size_ = size; }
    GSvector2 Size()const { return size_; }
    virtual GSuint Texture()const { return 0; }
    void Independent(int indep) { independent_ = indep; }
    int Independent() { return independent_; }
    bool IsbehindCamera() { return behindCamera_; }
protected:
    GSvector2 position_, size_;
    GScolor color_{ 1,1,1,1 };
    bool enable_{ true }, behindCamera_{ false };
    bool timeScaled_{ false };
    //カメラごとの独立UI
    int independent_{ 0 };
};

#endif
