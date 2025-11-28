#include "BossBattleStartEvent.h"
#include "../../World/IWorld.h"
#include "../../GameSystem/Event/TimeLine/TimeLine.h"
#include "../../Actor/Charactor/Enemy/Boss/Boss.h"
#include "../../Sound/SoundManager.h"
BossBattleStartEvent::BossBattleStartEvent(IWorld* world, Boss* boss,int invokeType, const GSvector3& position, GSvector2 size)
    :Event::Event(world, invokeType, position, size)
{
    world_ = world;
    boss_ = boss;
}

BossBattleStartEvent::~BossBattleStartEvent()
{
}

void BossBattleStartEvent::Update(float deltaTime)
{
    if (!world_->GetTimeLine().IsRunning()) {
        EndEvent();
    }
}

void BossBattleStartEvent::Draw() const
{
}

void BossBattleStartEvent::BeginEvent()
{
    world_->GetTimeLine().StartTimeLine("BossBattleStart");
    boss_->BeginIntro();
}

void BossBattleStartEvent::EndEvent()
{
    SoundManager::PlayBGM(Sound::BossBattle);
    //一度きりで終了（完全削除）
    isEnd_ = true;
}
