#ifndef FIELD_ACTOR_H_
#define FIELD_ACTOR_H_

#include "../../Actor/Actor.h"

// 前方宣言
class Ray;
class Line;
class BoundingSphere;

// フィールド用のアクタークラス
class FieldActor : public Actor {
public:
    FieldActor(const GSvector3& position,GSuint mesh, GSuint meshCollider,float rotate = 0);
    ~FieldActor();
    virtual void Update(float deltaTime)override;
    // 描画
    virtual void Draw() const override;

    // レイとの衝突判定
    bool Collide(
        const Ray& ray, float max_distance,
        GSvector3* intersect = nullptr, GSplane* plane = nullptr) const;
    // 線分との衝突判定
    bool Collide(
        const Line& line,
        GSvector3* intersect = nullptr, GSplane* plane = nullptr) const;
    // 球体との衝突判定
    bool Collide(
        const BoundingSphere& sphere,
        GSvector3* intersect = nullptr) const;

    GSuint GetMesh();
    void SetMesh(GSuint mesh);

    int GetStageID();
protected:
    // メッシュ
    GSuint          mesh_{ 0 };
    // メッシュコライダ
    GSuint          mesh_collider_{ 0 };
private:
    float yaw_{ 0 };
    int stageID_{ 0 };
    bool isEdit_{ false };
};

#endif
