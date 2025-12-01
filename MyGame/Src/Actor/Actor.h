#ifndef ACTOR_H_
#define ACTOR_H_

#include <gslib.h>
#include <GStransform.h>
#include "BoundingSphere.h"
#include "../Screen.h"
#include "AnimatedMesh/AnimatedMesh.h"
#include "../NameTag.h"

#include <string>

class IWorld;
class Actor
{
public:
    Actor() {};
    Actor(GSuint mesh,const GSvector3& position = { 0,0,0 },const GSvector3& rotate = { 0,0,0 });
    virtual ~Actor();
    virtual void Update(float deltaTime);
    virtual void LateUpdate(float deltaTime);
    virtual void Draw()const;
    virtual void React(Actor& other) {};
    virtual void Collide(Actor& other);

    bool IsCollide(const Actor& other)const;
    bool IsDead()const;
    const GStransform& Transform()const;
    GStransform& Transform();
    const BoundingSphere& Collider()const;
    void ChangeMotion(int motion, bool loop = true, float motionSpeed = 1, float motionTime = 0, float lerpTime = 0, bool forceChange = false);
    AnimatedMesh* GetMesh();
    void Die();
    void SetEnable(bool enable);
    std::string GetName();
    std::string GetTag();
    bool IsEnable()const;

    Actor(const Actor& other) = delete;
    Actor& operator=(const Actor& other) = delete;

    //デバック
    virtual void Debug(float deltaTime) {};
    void ColliderView(bool edit) { collider_.Edit(edit); };
protected:
    //前フレームからの経過秒数を返す
    float DeltaSeconds(float deltaTime);

    IWorld* world_{ nullptr };
    GStransform transform_;
    BoundingSphere collider_;
    AnimatedMesh* mesh_{ nullptr };

    bool dead_{ false };
    bool enable_{ true };

    //タグ名
    std::string     tag_{ ActorName::None };
    //名前
    std::string     name_{ ActorName::None };
    //移動量
    GSvector3       velocity_{ 0.0f, 0.0f, 0.0f };
    //コライダーのオフセット
    GSvector3       colliderOffset_{ 0.0f,0.0f,0.0f };
    //衝突判定が有効か？
    bool            enable_collider_{ true };
};

#endif
