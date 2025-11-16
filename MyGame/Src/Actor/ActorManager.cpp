#include "ActorManager.h"
#include "Actor.h"
#include "Charactor.h"
#include "Player/Player.h"
#include "../World/IWorld.h"
#include "imgui/imgui.h"

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
    //プレイヤー処理を優先したい為先頭に配置
    charactors_.insert(charactors_.begin(),player_);
}

void ActorManager::AddActor(Actor* actor)
{
    actors_.push_back(actor);
}

void ActorManager::AddCharactor(Charactor* charactor)
{
    charactors_.push_back(charactor);
}

void ActorManager::Update(float deltaTime)
{
    //ActorUpdate(deltaTime, *player_);
    ActorListUpdate(deltaTime, actors_);
    CharactorListUpdate(deltaTime, charactors_);
}

void ActorManager::LateUpdate(float deltaTime)
{
    //ActorLateUpdate(deltaTime, *player_);
    ActorListLateUpdate(deltaTime, actors_);
    CharactorListLateUpdate(deltaTime, charactors_);
}

void ActorManager::Draw() const
{
    //ActorDraw(*player_);
    ActorListDraw(actors_);
    CharactorListDraw(charactors_);
}

//プレイヤーとの衝突判定実行
void ActorManager::Collide()
{

    for (auto charactor = charactors_.begin(); charactor != charactors_.end(); ++charactor)
    {
        //オブジェクトとの当たり判定
        for (auto actor : actors_) {
            ActorCollide(**charactor, *actor);
        }
        //キャラ同士の当たり判定
        for (auto nextChara = std::next(charactor); nextChara != charactors_.end(); ++nextChara)
        {
            ActorCollide(**charactor, **nextChara);
        }
    }
    //仮で敵を倒し切ったら遷移
    int testEnemyCount = 0;
    for (auto chara : charactors_) {
        if (chara->GetTag() == ActorTag::Enemy) testEnemyCount++;
    }
    for (auto chara : charactors_) {
        if (chara->GetTag() == ActorTag::Player && testEnemyCount == 0) {
            chara->World()->IsEnd(true);
        }
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

    for (auto i = charactors_.begin(); i != charactors_.end();)
    {
        if ((*i)->IsDead())
        {
            delete* i;
            i = charactors_.erase(i);
        }
        else ++i;
    }
}

void ActorManager::Clear()
{
    for (auto actor : actors_)
    {
        delete actor;
    }
    actors_.clear();

    for (auto charactor : charactors_)
    {
        delete charactor;
    }
    player_ = nullptr;
    charactors_.clear();
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

Actor* ActorManager::GetAllActor(std::string name)
{
    Actor* findActor;
    findActor = GetActor(name);
    if (findActor) return findActor;

    Actor* findCharactor;
    findCharactor = GetCharactor(name);
    if (findCharactor) return findCharactor;

    return nullptr;
}

Actor* ActorManager::GetActor(int index)
{
    return actors_[index];
}

Actor* ActorManager::GetActor(std::string name)
{
    //その他オブジェクト検索
    for (int i = 0; i < actors_.size();i++) {
        if (actors_[i]->GetName() == name) return actors_[i];
    }
    return nullptr;
}

Charactor* ActorManager::GetCharactor(std::string name)
{
    //キャラクター検索
    for (int i = 0; i < charactors_.size(); i++) {
        if (charactors_[i]->GetName() == name) return charactors_[i];
    }
    return nullptr;
}

void ActorManager::Debug(float deltaTime)
{
    const std::string buttonText = debugCollide_ ? "OFF" : "ON";

    ImGui::Begin("Collider");
    ImGui::Text("ActorCollide:");
    ImGui::SameLine();
    if (ImGui::Button(buttonText.c_str(), ImVec2(40, 20))) {
        debugCollide_ = !debugCollide_;
        ColliderView(debugCollide_);
    }
    ImGui::End();

    //キャラクターのデバック
    for (auto chara : charactors_) {
        chara->Debug(deltaTime);
    }
    //その他Objectのデバック
    for (auto actor : actors_) {
        actor->Debug(deltaTime);
    }
}

void ActorManager::ColliderView(bool enable)
{
    for (auto chara : charactors_) {
        chara->ColliderView(debugCollide_);
    }
    for (auto actor : actors_) {
        actor->ColliderView(debugCollide_);
    }
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

void ActorManager::CharactorListUpdate(float deltaTime, std::vector<Charactor*>& actors)
{
    for (auto charactor : actors)
    {
        charactor->Update(deltaTime);
    }
}

void ActorManager::CharactorListLateUpdate(float deltaTime, std::vector<Charactor*>& actors)
{
    for (auto charactor : actors)
    {
        charactor->LateUpdate(deltaTime);
    }
}

void ActorManager::CharactorListDraw(std::vector<Charactor*> actors, bool isShadow) const
{
    for (auto charactor : actors)
    {
        charactor->Draw();
    }
}

void ActorManager::ActorCollide(Actor& other1, Actor& other2)
{
    if (!(other1.GetEnable() && other2.GetEnable()))return;
    bool enableCollider = other1.Collider().Enable() && other2.Collider().Enable();
    if (!enableCollider)return;
    float collideDistance = other1.Collider().Radius() + other2.Collider().Radius();
    GSvector3 collideVector = other1.Transform().position() - other2.Collider().Position();
    collideDistance -= collideVector.magnitude();
    if (collideDistance <= 0)return;
    other2.React(other1);
    other1.React(other2);
    collideDistance = MAX(collideDistance - 0.5f, 0);
    collideVector.y = 0;
    
    //どちらかのTriggerがtrueならすり抜け
    bool collideTrigger = other2.Collider().Trigger() || other1.Collider().Trigger();
    if (collideTrigger) return;
    //player(動いているオブジェクトを止める)
    other1.Transform().translate(collideVector.normalized() * collideDistance, GStransform::Space::World);
}

