#include "SoundMenu.h"
#include "GUI.h"
#include "ButtonList/VerticalButtonList.h"
#include "ButtonList/Button.h"
#include "ButtonList/ButtonSlider.h"
#include "../Sound/SoundManager.h"
#include "../Graphics/Effect/PostEffect.h"

SoundMenu::SoundMenu()
{
    SoundSettings();
}

void SoundMenu::Draw()const
{
    if (!enable_)return;
    guiManager_.Draw();
}

void SoundMenu::Update(float deltaTime)
{
    if (!enable_)return;
    guiManager_.Update(deltaTime, deltaTime);
}

void SoundMenu::SoundSettings()
{
    soundMenu_ = new VerticalButtonList({ Screen::HalfWidth - 100, 256 + 100 }, 5, 100);
    soundMenu_->AddButton(new ButtonSlider(Texture::SoundAll, [](float v) {SoundManager::SetMasterVolume(v); }, SoundManager::GetMasterVolume(), 0.1f, 0, 1));
    soundMenu_->AddButton(new ButtonSlider(Texture::SoundBGM, [](float v) {SoundManager::SetBGMVolume(v); }, SoundManager::GetBGMVolume(), 0.1f, 0, 1));
    soundMenu_->AddButton(new ButtonSlider(Texture::SoundSE, [](float v) {SoundManager::SetAllSEVolume(v); }, SoundManager::GetSEAllVolume(), 0.1f, 0, 1));
    guiManager_.AddGUI(soundMenu_);
    enable_ = false;
}

void SoundMenu::BeginSoundSetting()
{
    enable_ = true;
    PostEffect::Instance().IsBlur(true);
}

void SoundMenu::EndSoundSetting()
{
    enable_ = false;
    PostEffect::Instance().IsBlur(false);
}

bool SoundMenu::GameEnd()
{
    return gameEnd_;
}
