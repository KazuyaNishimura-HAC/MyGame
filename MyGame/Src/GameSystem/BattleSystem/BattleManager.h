#ifndef BATTLE_MANAGER_H_
#define BATTLE_MANAGER_H_
#include <vector>
class IWorld;
class Enemy;
class Event;
class Boss;

struct ResultData {
    ResultData(int maxCombo, int parryCount, int totalDamage, bool playerDead) :maxCombo{ maxCombo }, parryCount{ parryCount }, totalDamage{ totalDamage }, playerDead{ playerDead } {};
    ResultData() : ResultData(0, 0, 0,false) {};
    int maxCombo = 0;
    int parryCount = 0;
    int totalDamage = 0;
    bool playerDead = false;
};
class BattleManager
{
public:
    BattleManager(IWorld* world);
    ~BattleManager();
    void Update(float deltaTime);
    void EnemyDeadMessage(int group);
    void BossDeadMessage();
    bool IsBossDead() const;
    void PlayerDeadMessage();
    bool IsPlayerDead() const;
    bool GameEnd() const;
    void SetResultData(ResultData data);
    ResultData GetResultData()const ;
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
    bool playerDead_{ false };
    ResultData resultData_{};
};

#endif
