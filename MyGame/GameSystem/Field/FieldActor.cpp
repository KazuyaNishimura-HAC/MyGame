#include "FieldActor.h"
#include "Line.h"
#include "Ray.h"
#include "../../AssetID/Model.h"
#include "../../Actor/BoundingSphere.h"

FieldActor::FieldActor(const GSvector3& position, GSuint mesh,GSuint meshCollider, float rotate)
    :mesh_{ mesh }, mesh_collider_{ meshCollider }
{
    transform_.position(position);
    transform_.eulerAngles(0,rotate,0);
}

FieldActor::~FieldActor()
{
}

void FieldActor::Update(float deltaTime)
{
}

// 描画
void FieldActor::Draw() const {
    // メッシュの描画
    glPushMatrix();
    glMultMatrixf(transform_.localToWorldMatrix());
    gsDrawMesh(mesh_);
    glPopMatrix();
}

// レイとの衝突判定
bool FieldActor::Collide(const Ray& ray, float max_distance, GSvector3* intersect, GSplane* plane) const {
    // レイのパラメータを線分に変換
    Line line;
    line.start = ray.position;
    line.end = ray.position + (ray.direction.normalized() * max_distance);
    // 線分との衝突判定を行う
    return Collide(line, intersect, plane);
}

// 線分との衝突判定
bool FieldActor::Collide(const Line& line, GSvector3* intersect, GSplane* plane) const {
    // ローカル座標系の線分を求める
    Line localLine;
    localLine.start = transform_.inverseTransformPoint(line.start);
    localLine.end = transform_.inverseTransformPoint(line.end);
    // メッシュと線分が交差したか？
    if (gsCollisionMeshAndLine(gsGetMesh(mesh_collider_), &localLine.start, &localLine.end, intersect, plane) == GS_TRUE) {
        if (intersect != nullptr) {
            // 交点をワールド座標系に変換
            *intersect = transform_.transformPoint(*intersect);
        }
        if (plane != nullptr) {
            // 平面の方程式をワールド座標系に変換
            const GSmatrix4& local_to_world_matrix = transform_.localToWorldMatrix();
            gsPlaneTransform(plane, plane, &local_to_world_matrix);
        }
        return true;
    }
    return false;
}

// 球体との衝突判定
bool FieldActor::Collide(const BoundingSphere& sphere, GSvector3* collided_center) const {
    // ローカル座標系の球体を求める
    BoundingSphere localSphere;
    localSphere.position = transform_.inverseTransformPoint(sphere.position);
    localSphere.radius = sphere.radius;
    // メッシュと球体が衝突したか？
    GSvector3 local_collided_center;
    if (gsCollisionMeshAndSphere(gsGetMesh(mesh_collider_), &localSphere.position, localSphere.radius, &local_collided_center) == GS_TRUE) {
        if (collided_center != nullptr) {
            // 衝突判定後の中心座標をワールド座標系に変換
            *collided_center = transform_.transformPoint(local_collided_center);
        }
        return true;
    }
    return false;
}

GSuint FieldActor::GetMesh()
{
    return mesh_;
}

void FieldActor::SetMesh(GSuint mesh)
{
    mesh_ = mesh;
}

int FieldActor::GetStageID()
{
    int rotate = transform_.eulerAngles().y;

    if (mesh_ == Model::StraightRoad) {
        stageID_ = 1;
        if (rotate == 90 || rotate == 270) stageID_ = 2;
    }
    if (mesh_ == Model::HoleRoad) {
        stageID_ = 3;
        if (rotate == 90 || rotate == 270) stageID_ = 4;
    }
    if (mesh_ == Model::LeftCurvingRoad4) {
        stageID_ = 5;
        if (rotate == 90) stageID_ = 6;
        if (rotate == 180) stageID_ = 7;
        if (rotate == 270) stageID_ = 8;
    }
    if (mesh_ == Model::LeftCurvingRoad3) {
        stageID_ = 9;
        if (rotate == 90) stageID_ = 10;
        if (rotate == 180) stageID_ = 11;
        if (rotate == 270) stageID_ = 12;
    }
    if (mesh_ == Model::LeftCurvingRoad2) {
        stageID_ = 13;
        if (rotate == 90) stageID_ = 14;
        if (rotate == 180) stageID_ = 15;
        if (rotate == 270) stageID_ = 16;
    }
    if (mesh_ == Model::LeftCurvingRoad) {
        stageID_ = 17;
        if (rotate == 90) stageID_ = 18;
        if (rotate == 180) stageID_ = 19;
        if (rotate == 270) stageID_ = 20;
    }
    if (mesh_ == Model::RightCurvingRoad4) {
        stageID_ = 21;
        if (rotate == 90) stageID_ = 22;
        if (rotate == 180) stageID_ = 23;
        if (rotate == 270) stageID_ = 24;
    }
    if (mesh_ == Model::RightCurvingRoad3) {
        stageID_ = 25;
        if (rotate == 90) stageID_ = 26;
        if (rotate == 180) stageID_ = 27;
        if (rotate == 270) stageID_ = 28;
    }
    if (mesh_ == Model::RightCurvingRoad2) {
        stageID_ = 29;
        if (rotate == 90) stageID_ = 30;
        if (rotate == 180) stageID_ = 31;
        if (rotate == 270) stageID_ = 32;
    }
    if (mesh_ == Model::RightCurvingRoad) {
        stageID_ = 33;
        if (rotate == 90) stageID_ = 34;
        if (rotate == 180) stageID_ = 35;
        if (rotate == 270) stageID_ = 36;
    }
    if (mesh_ == Model::LeftStraightRoad) {
        stageID_ = 37;
        if (rotate == 90 || rotate == 270) stageID_ = 38;
    }
    if (mesh_ == Model::MiddleStraightRoad) {
        stageID_ = 39;
        if (rotate == 90 || rotate == 270) stageID_ = 40;
    }
    if (mesh_ == Model::SharpLeftCurvingRoad) {
        stageID_ = 41;
        if (rotate == 90) stageID_ = 42;
        if (rotate == 180) stageID_ = 43;
        if (rotate == 270) stageID_ = 44;
    }
    if (mesh_ == Model::SharpRightCurvingRoad) {
        stageID_ = 45;
        if (rotate == 90) stageID_ = 46;
        if (rotate == 180) stageID_ = 47;
        if (rotate == 270) stageID_ = 48;
    }
    return stageID_;
}

