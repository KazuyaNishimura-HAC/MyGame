#include "Field.h"
//Debu表示用
#include <GL/glut.h>

Field::Field(const GSvector3& position, const GSvector3& size, bool cameraCollide)
{
    transform_.localPosition(position);
    transform_.localScale(size);
    cameraCollide_ = cameraCollide;
}

GSvector3 Field::ClampPosition(const GSvector3& actorPosition, float radius)
{
    GSvector3 clampedPosition = actorPosition;
    GSvector3 distance = transform_.position() - actorPosition;
    GSvector3 size = CollisionExtents(radius);
    //XZ軸内ならクランプ
    if (IsInside(distance, size))
    {
        if (abs(distance.x) / size.x > abs(distance.z) / size.z)
            clampedPosition.x = transform_.position().x + size.x * (distance.x > 0 ? -1 : 1);
        else
            clampedPosition.z = transform_.position().z + size.z * (distance.z > 0 ? -1 : 1);
    }
    return clampedPosition;
}

void Field::Draw() const
{
    const GSvector3& pos = transform_.position();
    const GSvector3& size = transform_.localScale();
    glPushMatrix();
        // ライティング無効化
        glDisable(GL_LIGHTING);
        glTranslatef(pos.x, pos.y, pos.z);
        glScalef(size.x, size.y, size.z);   // X, Y, Z軸に沿って伸縮
        glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
        glutSolidCube(1.0f);  // 1辺=1の立方体をスケーリングして長方形にする
        //初期化
        glColor4f(1,1,1,1);
        // ライティング有効化
        glEnable(GL_LIGHTING);
    glPopMatrix();
}

void Field::Enable(bool enable)
{
    enable_ = enable;
}

bool Field::Enable() const
{
    return enable_;
}

void Field::Die()
{
    dead_ = true;
}

bool Field::IsDead() const
{
    return dead_;
}

void Field::CameraCollide(bool collide)
{
    cameraCollide_ = collide;
}

bool Field::CameraCollide() const
{
    return cameraCollide_;
}

//判定サイズをActorCollideの半径分広げる
GSvector3 Field::CollisionExtents(float radius)
{
    return transform_.localScale() / 2 + GSvector3::one() * radius;
}
//範囲内か？
bool Field::IsInside(const GSvector3& dist, const GSvector3& size)
{
    return abs(dist.x) < size.x && abs(dist.z) < size.z;
}
