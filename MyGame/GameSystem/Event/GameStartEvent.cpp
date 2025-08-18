#include "GameStartEvent.h"
#include "../../UI/Image.h"
#include "../../UI/Texture.h"
#include "../../Actor/Charactor/Player/Player.h"
#include "../../Sound/SoundManager.h"
#include "../../GameSystem/InputSystem/InputSystem.h"

GameStartEvent::GameStartEvent(IWorld* world, const GSvector3& position,GSvector2 size)
    :Event::Event(world,position,size)
{
   countDown_.push_back(new Image({ Screen::HalfWidth,Screen::HalfHeight }, Texture::Count3, {0.5f,0.5f}));
   countDown_.push_back(new Image({ Screen::HalfWidth,Screen::HalfHeight }, Texture::Count2, { 0.5f,0.5f }));
   countDown_.push_back(new Image({ Screen::HalfWidth,Screen::HalfHeight }, Texture::Count1, { 0.5f,0.5f }));
   countDown_.push_back(new Image({ Screen::HalfWidth,Screen::HalfHeight }, Texture::CountGO, { 0.5f,0.5f }));
   for (auto img : countDown_) {
       world->AddGUI(img);
       img->Enable(false);
   }

   controllerGuide_ = new BlinkingImage({ Screen::HalfWidth,Screen::HalfHeight }, Texture::ControllerGuide,{1,1},5);
   world->AddGUI(controllerGuide_);
   controllerGuide_->Alpha(0.01f);
   controllerGuide_->ApplyAmount(true);
   controllerGuide_->Enable(false);
}

void GameStartEvent::Update(float deltaTime)
{
    if (sequence_ == 0 && controllerGuide_->Enable()) {
        GuideUI();
        return;
    }
    //time_が0になったら以下を実行
    if (!EventWait(deltaTime))return;
    if (sequence_ >= 4)
    {
        EndEvent();
        return;
    }
    sequence_++;
    timer_ = countDownTime;
    if (sequence_ == 1) SoundManager::PlaySE(Sound::SE::CountDown);
}

void GameStartEvent::Draw() const
{
    int count = 0;
    for (auto img : countDown_) {
        count++;
        img->Enable(false);
        if(count == sequence_)img->Enable(true);
    }
}

void GameStartEvent::BeginEvent()
{
    controllerGuide_->Enable(true);
}

void GameStartEvent::EndEvent()
{
    world_->IsStart(true);
    SoundManager::PlayBGM(Sound::Stage1BGM);
    for (auto ui : countDown_) {
        ui->End();
    }
    countDown_.clear();
    isEnd_ = true;
}

void GameStartEvent::GuideUI()
{
    if (controllerGuide_->GetAlpha() >= 1.0f) {
        controllerGuide_->IsBlink(false);
        if (InputSystem::InputSystem::ButtonTrigger(InputSystem::Button::A)) controllerGuide_->IsBlink(true);
    }
    //ボタンが押されUIが消えたら次イベント
    if (controllerGuide_->GetAlpha() <= 0.0f) controllerGuide_->Enable(false);
}
