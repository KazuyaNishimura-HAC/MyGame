#ifndef ACTOR_MANAGER_H_
#define ACTOR_MANAGER_H_

#include <list>
#include <vector>
#include <string>

class Actor;
class Player;

class ActorManager
{
public:
    ActorManager();
    ~ActorManager();

    void AddPlayer(Player* player);
    void AddActor(Actor* actor);

    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void Draw()const;

    void Collide();
    void Remove();
    void Clear();
    void ActorEnable(bool enable);

    ActorManager(const ActorManager& other) = delete;
    ActorManager& operator=(const ActorManager& other) = delete;

    Player* GetPlayer();
    Actor* GetActor(int index);
    Actor* GetActor(std::string string);

    void Debug(float deltaTime);
private:
    void ActorUpdate(float deltaTime, Actor& actor);
    void ActorLateUpdate(float deltaTime, Actor& actor);
    void ActorDraw(Actor& actor)const;
    void ActorListUpdate(float deltaTime, std::vector<Actor*>& actors);
    void ActorListLateUpdate(float deltaTime, std::vector<Actor*>& actors);
    void ActorListDraw(std::vector<Actor*> actors, bool isShadow = false)const;
    void ActorCollide(Actor& player, Actor& other);

    Player* player_{ nullptr };
    std::vector<Actor*>actors_;
};

#endif
