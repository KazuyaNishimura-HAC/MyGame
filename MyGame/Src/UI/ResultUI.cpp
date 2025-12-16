#include "ResultUI.h"
#include "../World/IWorld.h"
#include "../Graphics/Effect/PostEffect.h"
#include "../UI/Image.h"
#include "../GameSystem/InputSystem/InputSystem.h"
#include "../UI/ValueText.h"

ResultUI::ResultUI(IWorld* world, const GSvector2& position)
    :GUI(position)
{
    world_ = world;
    enable_ = false;
    isResultOpen_ = false;
    rankText_ = new Image(position + GSvector2{ Screen::ScreenWidth - 700 , Screen::HalfHeight}, Texture::Data(Texture::RankText, { 0.5f,0.5f }), { 0.25f,0.25f });
    resultTexts_.push_back(new Image(position + GSvector2{ 100 , 300 }, Texture::Data(Texture::MaxComboText, { 0,0 }), { 0.25f,0.25f }));
    resultTexts_.push_back(new Image(position + GSvector2{ 100 , 400 }, Texture::Data(Texture::ParryCountText, { 0,0 }), { 0.25f,0.25f }));
    resultTexts_.push_back(new Image(position + GSvector2{ 100 , 500 }, Texture::Data(Texture::TotalDamageText, { 0,0 }), { 0.25f,0.25f }));

    valueTexts_.push_back(new ValueText(position + GSvector2{ 900, 300 }, { 0.25f,0.25f }));
    valueTexts_.push_back(new ValueText(position + GSvector2{ 900, 400 }, { 0.25f,0.25f }));
    valueTexts_.push_back(new ValueText(position + GSvector2{ 900, 500 }, { 0.25f,0.25f }));
}

ResultUI::~ResultUI()
{
    delete rankText_;
    rankText_ = nullptr;
    delete scoreRank_;
    scoreRank_ = nullptr;
    for (auto& text : resultTexts_) {
        delete text;
        text = nullptr;
    }
    for (auto& text : valueTexts_) {
        delete text;
        text = nullptr;
    }
}

void ResultUI::Update(float deltaTime)
{
    if (!enable_ || !isResultOpen_) return;
    if (InputSystem::ButtonTrigger(InputSystem::Button::B)) {
        EndResult();
    }
    int count = 0;
    for (auto& text : valueTexts_) {
        text->UpdateValue(valuesIndex_[count]);
        count++;
    }
}

void ResultUI::Draw() const
{
    if (!enable_ || !isResultOpen_) return;
    rankText_->Draw();
    if(scoreRank_ != nullptr)scoreRank_->Draw();
    for (auto& text : resultTexts_) {
        text->Draw();
    }
    for (auto& text : valueTexts_) {
        text->Draw();
    }
}

void ResultUI::BeginResult(ResultData data)
{
    //その他UIを非表示
    world_->Message(WorldMessage::GUIEnableFalse);
    enable_ = true;
    isResultOpen_ = true;
    world_->Message(WorldMessage::GamePause);
    PostEffect::Instance().IsBlur(true);
    data_ = data;
    valuesIndex_[0] = data.maxCombo;
    valuesIndex_[1] = data.parryCount;
    valuesIndex_[2] = data.totalDamage;
    int texture;
    if (data.playerDead) texture = Texture::RankC;
    else texture = Texture::RankS;
    scoreRank_ = new Image(position_ + GSvector2{ Screen::ScreenWidth - 400, Screen::HalfHeight }, Texture::Data(texture, { 0.5f,0.5f }), { 0.5f,0.5f });
}

bool ResultUI::IsResult() const
{
    return isResultOpen_;
}

void ResultUI::EndResult()
{
    enable_ = false;
    isResultOpen_ = false;
    PostEffect::Instance().IsBlur(false);
    world_->Message(WorldMessage::PauseEnd);
    world_->Message(WorldMessage::GameEnd);
}
