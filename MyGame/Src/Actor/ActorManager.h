#ifndef ACTOR_MANAGER_H_
#define ACTOR_MANAGER_H_

#include <list>
#include <vector>
#include <string>

class Actor;
class Charactor;
class Player;

class ActorManager
{
public:
    ActorManager();
    ~ActorManager();

    void AddPlayer(Player* player);
    void AddActor(Actor* actor);
    void AddCharactor(Charactor* charactor);

    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void Draw()const;
    void ShadowDraw()const;

    void Collide();
    void Remove();
    void Clear();
    void ActorEnable(bool enable);

    ActorManager(const ActorManager& other) = delete;
    ActorManager& operator=(const ActorManager& other) = delete;

    Player* GetPlayer();
    Actor* GetAllActor(std::string name);
    Actor* GetActor(int index);
    Actor* GetActor(std::string name);
    Charactor* GetCharactor(std::string name);
    std::vector<Charactor*> GetCharactorList();
    void Debug(float deltaTime);
    void ColliderView(bool enable);
private:
    void ActorUpdate(float deltaTime, Actor& actor);
    void ActorLateUpdate(float deltaTime, Actor& actor);
    void ActorDraw(Actor& actor)const;
    void ActorListUpdate(float deltaTime, std::vector<Actor*>& actors);
    void ActorListLateUpdate(float deltaTime, std::vector<Actor*>& actors);
    void ActorListDraw(std::vector<Actor*> actors, bool isShadow = false)const;

    void CharactorListUpdate(float deltaTime, std::vector<Charactor*>& actors);
    void CharactorListLateUpdate(float deltaTime, std::vector<Charactor*>& actors);
    void CharactorListDraw(std::vector<Charactor*> actors, bool isShadow = false)const;

    void ActorCollide(Actor& other1, Actor& other2);

    Player* player_{ nullptr };
    std::vector<Actor*>actors_;
    std::vector<Charactor*>charactors_;
    bool debugCollide_{ false };
};

#endif
