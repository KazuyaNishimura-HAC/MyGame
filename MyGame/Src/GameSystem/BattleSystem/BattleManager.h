#ifndef BATTLE_MANAGER_H_
#define BATTLE_MANAGER_H_
#include <vector>
class IWorld;
class Enemy;
class Event;
class Boss;

class BattleManager
{
public:
    BattleManager(IWorld* world);
    ~BattleManager();
    void Update(float deltaTime);
    void EnemyDeadMessage(int group);
    void BossDeadMessage();
    bool IsBossDead() const;
private:
    void SpawnPlayer();
    void SpawnEnemis();
    void AddBattleEvent();
    void BeginEvent(int group);
    std::vector<std::vector<Enemy*>> groupEnemis_;
    Boss* boss_{ nullptr };
    std::vector<int>groupCount_;
    IWorld* world_{ nullptr };
    std::vector<Event*> openDoorEvents_;
    const int enemyGroupCount_{ 4 };
    int battleEventCount_{ 0 };
    bool bossDead_{ false };
};

#endif
