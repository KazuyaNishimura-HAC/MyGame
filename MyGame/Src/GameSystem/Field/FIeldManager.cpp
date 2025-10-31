#include "FieldManager.h"
#include "FieldActor.h"
#include "Line.h"
#include "Ray.h"
#include "../../Actor/BoundingSphere.h"
#include "../../GameSystem/Field/FieldActor.h"
#include "../../GameSystem/Field/Field.h"
#include <limits> // numeric_limitsを使うのに必要

FieldManager::FieldManager()
{

}

FieldManager::~FieldManager()
{
    Clear();
}

void FieldManager::Update(float delta_time)
{
    for (auto field : fieldActor_)
    {
        field->Update(delta_time);
    }
}

void FieldManager::Draw(Camera* camera) const
{
#if _DEBUG
    for (auto field : fields_)
    {
        field->Draw();
    }
#endif
    for (auto field : fieldActor_)
    {
        if (camera != nullptr && camera->IsVisible(field->Transform().position())) {
            field->Draw();
        }
    }
    
}

void FieldManager::AddField(FieldActor* field)
{
    fieldActor_.push_back(field);
}

void FieldManager::AddField(Field* field)
{
    fields_.push_back(field);
}

FieldActor* FieldManager::GetField(int index)
{
    return fieldActor_[index];
}

FieldActor* FieldManager::GetFieldID(int index,int id)
{
    return nullptr;
}

int FieldManager::GetFieldCount()
{
    return fieldActor_.size();
}

void FieldManager::CollideActor(GStransform& transform)
{
    transform.position(ClampPosition(transform.position(), 0.5f));
}

GSvector3 FieldManager::ClampPosition(const GSvector3& position, float radius)
{
    GSvector3 clampedPos = position;

    for (auto field : fields_)
    {
        if (!field->Enable())continue;

        clampedPos = field->ClampPosition(clampedPos, radius);
    }
    return clampedPos;
}
void FieldManager::Remove()
{
    for (auto i = fieldActor_.begin(); i != fieldActor_.end();)
    {
        if ((*i)->IsDead())
        {
            delete* i;
            i = fieldActor_.erase(i);
        }
        else ++i;
    }

    for (auto i = fields_.begin(); i != fields_.end();)
    {
        if ((*i)->IsDead())
        {
            delete* i;
            i = fields_.erase(i);
        }
        else ++i;
    }
}

void FieldManager::Clear()
{
    for (auto field : fieldActor_)
    {
        delete field;
    }
    fieldActor_.clear();

    for (auto field : fields_)
    {
        delete field;
    }
    fields_.clear();
}

// レイとフィールド用のアクターとの衝突判定
FieldActor* FieldManager::GetCollideField(const Ray& ray, float max_distance, GSvector3* intersect, GSplane* plane) const {
    // レイを線分に変換する
    Line line;
    line.start = ray.position;
    line.end = ray.position + (ray.direction.normalized() * max_distance);
    // 線分との判定を行う
    return GetCollideField(line, intersect, plane);
}

// 線分とフィールド用のアクターとの衝突判定
FieldActor* FieldManager::GetCollideField(const Line& line, GSvector3* intersect, GSplane* plane) const {
    // 最も始点から近いアクター
    FieldActor* closestActor{ nullptr };
    // 最も始点から近い交点との距離
    float closestDistance = std::numeric_limits<float>::max(); // float型の最大値
    // 最も始点から近い交点
    GSvector3 closestIntersection;
    // 最も始点から近い交点の平面
    GSplane closestIntersectionPlane;

    for (auto field : fieldActor_) {
        // フィールドアクターと線分との交差判定を行う
        GSvector3 intersection_point;
        GSplane intersection_plane;
        if (field->Collide(line, &intersection_point, &intersection_plane)) {
            // 始点からの距離を計算
            float distance = line.start.distance(intersection_point);
            if (distance < closestDistance) {
                // 距離が近い場合アクター更新
                closestDistance = distance;
                closestActor = field;
                closestIntersection = intersection_point;
                closestIntersectionPlane = intersection_plane;
            }
        }
    }
    // 衝突したアクターが存在するか？
    if (closestActor != nullptr) {
        if (intersect != nullptr) {
            *intersect = closestIntersection;
        }
        if (plane != nullptr) {
            *plane = closestIntersectionPlane;
        }
    }
    return closestActor; // 始点に最も近いアクターを返す
}

// 球体とフィールド用のアクターとの衝突判定
FieldActor* FieldManager::GetCollideField(const BoundingSphere& sphere, GSvector3* collided_center) const {
    for (auto field : fieldActor_) {
        // フィールドアクターと球体の衝突判定を行う
        if (field->Collide(sphere, collided_center)) {
            return field;
        }
    }
    return nullptr;
}

