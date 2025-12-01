#include "ResultUI.h"
#include "../World/IWorld.h"
#include "../Graphics/Effect/PostEffect.h"
#include "../UI/Image.h"
#include "../GameSystem/InputSystem/InputSystem.h"

ResultUI::ResultUI(IWorld* world, const GSvector2& position)
    :GUI(position)
{
    world_ = world;
    enable_ = false;
    resultText_ = new Image(position + GSvector2{ Screen::HalfWidth - 150 , Screen::HalfHeight}, Texture::Data(Texture::ResultText, { 0.5f,0.5f }), { 1.5f,1.5f });
    scoreRank_ = new Image(position + GSvector2{ Screen::HalfWidth + 200, Screen::HalfHeight }, Texture::Data(Texture::ScoreRankS, { 0.5f,0.5f }), { 3.0f,3.0f });
}

ResultUI::~ResultUI()
{
    delete resultText_;
    resultText_ = nullptr;
    delete scoreRank_;
    scoreRank_ = nullptr;
}

void ResultUI::Update(float deltaTime)
{
    if (!enable_) return;
    if (InputSystem::ButtonTrigger(InputSystem::Button::B)) {
        EndResult();
    }
}

void ResultUI::Draw() const
{
    if (!enable_) return;
    resultText_->Draw();
    scoreRank_->Draw();
}

void ResultUI::BeginResult()
{
    enable_ = true;
    world_->Message(WorldMessage::GamePause);
    PostEffect::Instance().IsBlur(true);
}

void ResultUI::EndResult()
{
    enable_ = false;
    PostEffect::Instance().IsBlur(false);
    world_->Message(WorldMessage::PauseEnd);
    world_->Message(WorldMessage::GameEnd);
}
