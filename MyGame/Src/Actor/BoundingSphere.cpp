#include "BoundingSphere.h"

BoundingSphere::BoundingSphere(float radius, const GSvector3& position, const GSvector3& color)
    : position{ position }, radius{ radius }, defColor_{ color }
{
}

void BoundingSphere::Position(const GSvector3& pos)
{
    position = pos;
}

GSvector3 BoundingSphere::Position() const
{
    return position;
}

bool BoundingSphere::Intersects(const BoundingSphere& other) const
{
    float length = (position - other.position).lengthSq();
    float dist = radius + other.radius;
    dist *= dist;
    return length <= dist;
}

void BoundingSphere::Draw() const
{
    //リリース時はコメント
#if _DEBUG
    glPushMatrix();          
        // ライティング無効化
        glDisable(GL_LIGHTING);
        glTranslatef(position.x, position.y, position.z);
        if(enable_) glColor3f(0.0f, 1.0f, 0.0f);
        glutWireSphere(radius, 16, 16);
        glColor3f(defColor_.x, defColor_.y, defColor_.z);
        // ライティングを戻す（必要なら）
        glEnable(GL_LIGHTING);
    glPopMatrix();
#endif
}

float BoundingSphere::Radius() const
{
    return radius;
}

void BoundingSphere::Radius(float rad)
{
    radius = rad;
}

bool BoundingSphere::Enable() const
{
    return enable_;
}

void BoundingSphere::Enable(bool enable)
{
    enable_ = enable;
}

bool BoundingSphere::Trigger() const
{
    return trigger_;
}

void BoundingSphere::Trigger(bool trigger)
{
    trigger_ = trigger;
}

void BoundingSphere::Color(GSvector3 color)
{
    defColor_ = color;
}

void BoundingSphere::Edit(bool edit)
{
    edit_ = edit;
}
