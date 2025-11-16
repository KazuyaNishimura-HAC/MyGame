#ifndef BOUNDING_SPHERE_H_
#define BOUNDING_SPHERE_H_

#include <gslib.h>

class BoundingSphere
{
public:
    BoundingSphere(float radius = 1, const GSvector3& position = { 0,0,0 },const GSvector3& color = {1.0f,1.0f,1.0f});

    void Position(const GSvector3& position);
    GSvector3 Position() const;
    bool Intersects(const BoundingSphere& other)const;
    void Draw()const;
    float Radius()const;
    void Radius(float radius);
    bool Enable()const;
    void Enable(bool enable);
    bool Trigger()const;
    void Trigger(bool trigger);
    void Color(GSvector3 color);
    void Edit(bool edit);
public:
    enum state{
        None,
        Enter,
        Triggers,
        Exit
    };
    int state{ None };
    float radius{ 1 };
    GSvector3 position;
    bool enable_{ true };
    bool trigger_{ false };
    bool edit_{ true };
    //デフォルトカラー(白色)
    GSvector3 defColor_;
    //編集中 
    GSvector3 editColor_{0.0f,1.0f,0.0f};
};

#endif
