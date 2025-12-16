#include "BossBattleStartEvent.h"
#include "../../World/IWorld.h"
#include "../../GameSystem/Event/TimeLine/TimeLine.h"
#include "../../Actor/Charactor/Enemy/Boss/Boss.h"
#include "../../Sound/SoundManager.h"
#include <GSgame.h>
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
    //タイムラインイベントが終わったらsっ有料
    if (!world_->GetTimeLine().IsRunning()) {
        EndEvent();
    }
    //bgm設定が完了したらreturn
    if (bgmReset_) return;
    if (currentVolume_ > 0.0f) {
        currentVolume_ -= deltaTime / 60.0f;
        SoundManager::SetBGMVolume(currentVolume_);
    }
    else {
        //非同期でサウンドを止める
        gslib::Game::run_thread([=] { StopBGM(); });
    }
}

void BossBattleStartEvent::Draw() const
{
}

void BossBattleStartEvent::StopBGM()
{
    SoundManager::StopBGM();
    SoundManager::SetBGMVolume(prevVolume_);
    bgmReset_ = true;
}

void BossBattleStartEvent::BeginEvent()
{
    world_->Message(WorldMessage::GUIEnableFalse);
    world_->GetTimeLine().StartTimeLine("BossBattleStart");
    boss_->BeginIntro();
    prevVolume_ = SoundManager::GetBGMVolume();
    currentVolume_ = prevVolume_;
    
}

void BossBattleStartEvent::EndEvent()
{
    world_->Message(WorldMessage::GUIEnableTrue);
    SoundManager::PlayBGM(Sound::BossBattle);
    //一度きりで終了（完全削除）
    isEnd_ = true;
}
