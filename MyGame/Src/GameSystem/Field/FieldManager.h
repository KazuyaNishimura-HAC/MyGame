#ifndef FIELD_MANAGER_H_
#define FIELD_MANAGER_H_

#include "../../Actor/ActorManager.h"
#include "../Camera/Camera.h"
#include <vector>
class Ray;
class Line;
class BoundingSphere;
class FieldActor;
class Field;

// フィールドアクターマネージャー
class FieldManager {
public:
    FieldManager();
    ~FieldManager();

    void Update(float delta_time);
    void Draw(Camera* camera = nullptr) const;

    void AddField(FieldActor* field);
    void AddField(Field* field);
    FieldActor* GetField(int index);
    FieldActor* GetFieldID(int index,int id);
    int GetFieldCount();
    void CollideActor(GStransform& transform);
    GSvector3 ClampPosition(const GSvector3& position, float radius);
    void Remove();
    void Clear();
    // レイとの衝突判定
    FieldActor* GetCollideField(
        const Ray& ray, float max_distance,
        GSvector3* intersect = nullptr, GSplane* plane = nullptr) const;
    // 線分との衝突判定
    FieldActor* GetCollideField(
        const Line& line,
        GSvector3* intersect = nullptr, GSplane* plane = nullptr) const;
    // 球体との衝突判定
    FieldActor* GetCollideField(
        const BoundingSphere& sphere,
        GSvector3* collided_center = nullptr) const;

    // コピー禁止
    FieldManager(const FieldManager& other) = delete;
    FieldManager& operator = (const FieldManager& other) = delete;

private:
    std::vector<FieldActor*> fieldActor_;
    std::vector<Field*>fields_;
};

#endif
