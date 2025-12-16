#include "BattleManager.h"
#include "../../World/IWorld.h"
#include "../../Actor/Charactor/AllCharactors.h"
#include "../../GameSystem/Event/OpenDoorEvent.h"
#include "../../GameSystem/Event/BossBattleStartEvent.h"
BattleManager::BattleManager(IWorld* world)
{
    world_ = world;
    SpawnPlayer();
    SpawnEnemis();
    AddBattleEvent();
}

BattleManager::~BattleManager()
{
    groupCount_.clear();
    openDoorEvents_.clear();
}

void BattleManager::Update(float deltaTime)
{
}

void BattleManager::SpawnPlayer()
{
    Player* player = new Player(world_, { 0,0,0 }, { 0,90,0 }, Status{ 100, 10, 3 });
    player->Init(this);
    world_->AddPlayer(player);
}

void BattleManager::SpawnEnemis()
{
    //グループ数分要素を確保
    groupEnemis_.resize(enemyGroupCount_ + 1);
    groupCount_.resize(enemyGroupCount_ + 1);
    groupEnemis_[1].push_back(new SwordEnemy1(world_, 1, { 35,0,0 },{ 0,270,0 }, Status{ 150, 5, 0 }));
    groupEnemis_[2].push_back(new SwordEnemy1(world_, 2, { 85,0,-5 }, { 0,270,0 }, Status{ 150, 5, 0 }));
    groupEnemis_[2].push_back(new SwordEnemy1(world_, 2, { 85,0,5 }, { 0,270,0 }, Status{ 150, 5, 0 }));
    groupEnemis_[3].push_back(new SwordEnemy1(world_, 3, { 130,0,-5 }, { 0,270,0 }, Status{ 150, 5, 0 }));
    groupEnemis_[3].push_back(new SwordEnemy1(world_, 3, { 130,0,0 }, { 0,270,0 }, Status{ 150, 5, 0 }));
    groupEnemis_[3].push_back(new SwordEnemy1(world_, 3, { 130,0,5 }, { 0,270,0 }, Status{ 150, 5, 0 }));
    groupEnemis_[4].push_back(new SwordEnemy1(world_, 4, { 180,0,-5 }, { 0,270,0 }, Status{ 150, 5, 0 }));
    groupEnemis_[4].push_back(new SwordEnemy1(world_, 4, { 180,0,5 }, { 0,270,0 }, Status{ 150, 5, 0 }));
    groupEnemis_[4].push_back(new SwordEnemy1(world_, 4, { 180,0,-10 }, { 0,270,0 }, Status{ 150, 5, 0 }));
    groupEnemis_[4].push_back(new SwordEnemy1(world_, 4, { 180,0,10 }, { 0,270,0 }, Status{ 150, 5, 0 }));
    boss_ = new Boss(world_, 4, { 185,40,0 }, { 0,270,0 }, Status{ 1200, 15, 15 });
    groupEnemis_[4].push_back(boss_);
    for (int i = 0; i < enemyGroupCount_ + 1;++i) {
        groupCount_[i] = groupEnemis_[i].size();
        for (auto& enemy : groupEnemis_[i]) {
            //各エネミーにbattleManagerアドレスを渡す
            enemy->Init(this);
            world_->AddCharactor(enemy);
            //追加したらActorManagerに権利を渡す
            enemy = nullptr;
        }
    }
    groupEnemis_.clear();
}

void BattleManager::AddBattleEvent()
{
    openDoorEvents_.push_back(new OpenDoorEvent(world_, InvokeType::Manual, 1, { 48,0,0 }));
    openDoorEvents_.push_back(new OpenDoorEvent(world_, InvokeType::Manual, 2, { 94,0,0 }));
    openDoorEvents_.push_back(new OpenDoorEvent(world_, InvokeType::Manual, 3, { 140,0,0 }));
    for (auto& event : openDoorEvents_) {
        battleEventCount_++;
        world_->AddEvent(event);
    }
    world_->AddEvent(new BossBattleStartEvent(world_, boss_, InvokeType::Collision, { 165,0,0 }, { 3,10 }));
}

void BattleManager::EnemyDeadMessage(int group)
{
    if (group > enemyGroupCount_) return;
    //敵カウントを減らす
    groupCount_[group] -= 1;
    if (groupCount_[group] <= 0) BeginEvent(group);
}

void BattleManager::BossDeadMessage()
{
    bossDead_ = true;
}

bool BattleManager::IsBossDead() const
{
    return bossDead_;
}

void BattleManager::PlayerDeadMessage()
{
    playerDead_ = true;
}

bool BattleManager::IsPlayerDead() const
{
    return playerDead_;
}

bool BattleManager::GameEnd() const
{
    return playerDead_ || bossDead_;
}

void BattleManager::SetResultData(ResultData data)
{
    resultData_ = data;
}

ResultData BattleManager::GetResultData() const
{
    return resultData_;
}

void BattleManager::BeginEvent(int group)
{
    if (group > battleEventCount_ || group < 0) return;
    //イベント発火
    openDoorEvents_[group - 1]->SetInvoke(true);
    openDoorEvents_[group - 1] = nullptr;
}

