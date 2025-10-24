#include "Actor.h"

Actor::Actor(GSuint mesh)
    :mesh_{ new AnimatedMesh(mesh) }
{
}

Actor::~Actor()
{
    delete mesh_;
    mesh_ = nullptr;
}

void Actor::Update(float deltaTime)
{
    mesh_->Update(deltaTime);
}

void Actor::LateUpdate(float deltaTime)
{
    //現在座標をメッシュに反映
    mesh_->Transform(transform_.localToWorldMatrix());
}

void Actor::Draw() const
{
    mesh_->Draw();
}

void Actor::Collide(Actor& other)
{
    if (!collider_.Enable())return;

    if (IsCollide(other))
    {
        React(other);
        other.React(*this);
    }
}

void Actor::Die()
{
    dead_ = true;
}
//アクティブ設定
void Actor::SetEnable(bool enable)
{

    enable_ = enable;
}

std::string Actor::GetName()
{
    return name_;
}

std::string Actor::GetTag()
{
    return tag_;
}

bool Actor::GetEnable() const
{
    return enable_;
}

bool Actor::IsCollide(const Actor& other) const
{
    return collider_.Intersects(other.Collider());
}

bool Actor::IsDead() const
{
    return dead_;
}

const GStransform& Actor::Transform() const
{
    return transform_;
}

GStransform& Actor::Transform()
{
    return transform_;
}

const BoundingSphere& Actor::Collider() const
{
    return collider_;
}

void Actor::ChangeMotion(int motion, bool loop, float motionSpeed, float motionTime , float lerpTime , bool forceChange)
{
    mesh_->ChangeMotion(motion, loop, motionSpeed, motionTime, lerpTime, forceChange);
}

AnimatedMesh* Actor::GetMesh()
{
    return mesh_;
}

float Actor::DeltaSeconds(float deltaTime)
{
    return deltaTime / 60.0f;
}
