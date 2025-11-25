#include "BattleManager.h"
#include "../../World/IWorld.h"
#include "../../Actor/Charactor/AllCharactors.h"
#include "../../GameSystem/Event/OpenDoorEvent.h"
BattleManager::BattleManager(IWorld* world)
{
    world_ = world;
    openDoorEvents_.push_back(new OpenDoorEvent(world_, InvokeType::Manual,1));
    openDoorEvents_.push_back(new OpenDoorEvent(world_, InvokeType::Manual,2));
    openDoorEvents_.push_back(new OpenDoorEvent(world_, InvokeType::Manual,3));
    for (auto& event : openDoorEvents_) {
        battleEventCount_++;
        world_->AddEvent(event);
    }
    SpawnEnemis();
}

BattleManager::~BattleManager()
{
    groupCount_.clear();
    openDoorEvents_.clear();
}

void BattleManager::Update(float deltaTime)
{
}

void BattleManager::SpawnEnemis()
{
    //グループ数分要素を確保
    groupEnemis_.resize(enemyGroupCount_ + 1);
    groupCount_.resize(enemyGroupCount_ + 1);
    groupEnemis_[1].push_back(new SwordEnemy1(world_, 1, { 35,0,0 },{ 0,270,0 }));
    groupEnemis_[2].push_back(new SwordEnemy1(world_, 2, { 85,0,-5 }, { 0,270,0 }));
    groupEnemis_[2].push_back(new SwordEnemy1(world_, 2, { 85,0,5 }, { 0,270,0 }));
    groupEnemis_[3].push_back(new SwordEnemy1(world_, 3, { 130,0,-5 }, { 0,270,0 }));
    groupEnemis_[3].push_back(new SwordEnemy1(world_, 3, { 130,0,0 }, { 0,270,0 }));
    groupEnemis_[3].push_back(new SwordEnemy1(world_, 3, { 130,0,5 }, { 0,270,0 }));
    groupEnemis_[4].push_back(new SwordEnemy1(world_, 4, { 180,0,-5 }, { 0,270,0 }, Status{ 120, 5 }));
    groupEnemis_[4].push_back(new SwordEnemy1(world_, 4, { 180,0,5 }, { 0,270,0 }, Status{ 120, 5 }));
    groupEnemis_[4].push_back(new SwordEnemy1(world_, 4, { 180,0,-10 }, { 0,270,0 }, Status{ 120, 5 }));
    groupEnemis_[4].push_back(new SwordEnemy1(world_, 4, { 180,0,10 }, { 0,270,0 }, Status{ 120, 5 }));
    groupEnemis_[4].push_back(new Boss(world_, 4, { 185,0,0 }, { 0,270,0 }, Status{ 500, 30 }));
    for (int i = 0; i < enemyGroupCount_ + 1;++i) {
        groupCount_[i] = groupEnemis_[i].size();
        for (auto& enemy : groupEnemis_[i]) {
            world_->AddCharactor(enemy);
            //追加したらActorManagerに権利を渡す
            enemy = nullptr;
        }
    }
    groupEnemis_.clear();
}

void BattleManager::EnemyDeadMessage(int group)
{
    if (group > enemyGroupCount_) return;
    //敵カウントを減らす
    groupCount_[group] -= 1;
    if (groupCount_[group] <= 0) BeginEvent(group);
}

void BattleManager::BeginEvent(int group)
{
    if (group > battleEventCount_ || group < 0) return;
    //イベント発火
    openDoorEvents_[group - 1]->SetInvoke(true);
    openDoorEvents_[group - 1] = nullptr;
}

