#include "ActorManager.h"
#include "Actor.h"
#include "Player/Player.h"

ActorManager::ActorManager()
{
}

ActorManager::~ActorManager()
{
    Clear();
}

void ActorManager::AddPlayer(Player* player)
{
    delete player_;
    player_ = player;
}

void ActorManager::AddActor(Actor* actor)
{
    actors_.push_back(actor);
}

void ActorManager::Update(float deltaTime)
{
    ActorUpdate(deltaTime, *player_);
    ActorListUpdate(deltaTime, actors_);
}

void ActorManager::LateUpdate(float deltaTime)
{
    ActorLateUpdate(deltaTime, *player_);
    ActorListLateUpdate(deltaTime, actors_);
}

void ActorManager::Draw() const
{
    ActorDraw(*player_);
    ActorListDraw(actors_);
}

//プレイヤーとの衝突判定実行
void ActorManager::Collide()
{
    //キャラの当たり判定
    for (auto actor : actors_) {
        ActorCollide(*player_, *actor);
    }
}

void ActorManager::Remove()
{
    for (auto i = actors_.begin(); i != actors_.end();)
    {
        if ((*i)->IsDead())
        {
            delete* i;
            i = actors_.erase(i);
        }
        else ++i;
    }
}

void ActorManager::Clear()
{
    delete player_;
    player_ = nullptr;

    for (auto actor : actors_)
    {
        delete actor;
    }
    actors_.clear();
}

void ActorManager::ActorEnable(bool enable)
{
    for (auto actor : actors_)
    {
        actor->SetEnable(enable);
    }
}

Player* ActorManager::GetPlayer()
{
    return player_;
}

Actor* ActorManager::GetActor(int index)
{
    return actors_[index];
}

Actor* ActorManager::GetActor(std::string string)
{
    for (int i = 0; i < actors_.size();i++) {
        if (actors_[i]->GetName() == string) return actors_[i];
    }
    return nullptr;
}

void ActorManager::Debug(float deltaTime)
{
    player_->Debug(deltaTime);
}

void ActorManager::ActorUpdate(float deltaTime, Actor& actor)
{
    actor.Update(deltaTime);
}

void ActorManager::ActorLateUpdate(float deltaTime, Actor& actor)
{
    actor.LateUpdate(deltaTime);
}

void ActorManager::ActorDraw(Actor& actor) const
{
    actor.Draw();
}

void ActorManager::ActorListUpdate(float deltaTime, std::vector<Actor*>& actors)
{
    for (auto actor : actors)
    {
        actor->Update(deltaTime);
    }
}

void ActorManager::ActorListLateUpdate(float deltaTime, std::vector<Actor*>& actors)
{
    for (auto actor : actors)
    {
        actor->LateUpdate(deltaTime);
    }
}

void ActorManager::ActorListDraw(std::vector<Actor*> actors, bool isShadow) const
{
    for (auto actor : actors)
    {
        actor->Draw();
    }
}

void ActorManager::ActorCollide(Actor& player, Actor& other)
{
    if (!(player.GetEnable() && other.GetEnable()))return;

    bool enableCollider = player.Collider().Enable() && other.Collider().Enable();
    if (!enableCollider)return;

    float collideDistance = player.Collider().Radius() + other.Collider().Radius();
    GSvector3 collideVector = player.Transform().position() - other.Collider().Position();
    collideDistance -= collideVector.magnitude();
    if (collideDistance <= 0)return;

    other.React(player);
    player.React(other);
    collideDistance = MAX(collideDistance - 0.5f, 0);
    collideVector.y = 0;

    //どちらかのTriggerがtrueならすり抜け
    bool collideTrigger = other.Collider().Trigger() || player.Collider().Trigger();
    if (collideTrigger) return;
    //player(動いているオブジェクトを止める)
    player.Transform().translate(collideVector.normalized() * collideDistance, GStransform::Space::World);
}

