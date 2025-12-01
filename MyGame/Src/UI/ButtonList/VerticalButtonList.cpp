#include "VerticalButtonList.h"
#include "Button.h"
#include "ButtonSlider.h"
#include "../../GameSystem/InputSystem/InputSystem.h"
#include "../../Sound/SoundManager.h"
#include "../Texture.h"
#include "../../UI/Image.h"

VerticalButtonList::VerticalButtonList(GSvector2 position, int defalutIndex, float buttonDistance)
    :GUI(position), defaultIndex_{ defalutIndex }, buttonDistance_{ buttonDistance }
{
}

VerticalButtonList::~VerticalButtonList()
{
    for (auto button : buttons_)
    {
        delete button;
    }
    buttons_.clear();
    delete selectBuck_;
}

void VerticalButtonList::AddButton(Button* newButton,bool def)
{
    if (!def) newButton->SelectMove(def);
    newButton->SetPosition({ position_.x,position_.y + buttons_.size() * buttonDistance_ }, 0);
    buttons_.push_back(newButton);
    //1つ目のボタンは選択
    if (buttons_.size() > 1)return;
    newButton->OnSelect();
}

void VerticalButtonList::SelectBG(GSuint textureID, GSvector2 size,GSvector2 offset)
{
    //すでに中身がある場合メモリ解放
    delete selectBuck_;
    bgOffset_ = offset;
    selectBuck_ = new Image(buttons_[currentIndex_]->Position(), textureID, size);
}


void VerticalButtonList::Update(float deltaTime)
{
    if (!enable_)return;
    if (enabledFrameWait_)
    {
        enabledFrameWait_ = false;
        return;
    }
    Select();
    Confirm();
    for (auto button : buttons_)
    {
        button->Update(deltaTime);
    }
    if (selectBuck_ != nullptr) selectBuck_->Position(buttons_[currentIndex_]->Position() + bgOffset_);
    //キャンセル時
    /*if (!InputSystem::ButtonTrigger(InputSystem::Button::B))return;
    buttons_[currentIndex_]->OnDeSelect();
    buttons_[defaultIndex_]->OnSelect();
    buttons_[defaultIndex_]->OnConfirm();
    currentIndex_ = defaultIndex_;*/
}

void VerticalButtonList::Draw() const
{
    if (!enable_)return;
    if (selectBuck_ != nullptr) selectBuck_->Draw();
    for (auto button : buttons_)
    {
        button->Draw();
    }
    
}

void VerticalButtonList::Enable(bool enable)
{
    enabledFrameWait_ = true;
    if (!enable_ && enable)SoundManager::PlaySE(Sound::MenuPop);
    GUI::Enable(enable);
}

int VerticalButtonList::SelectIndex()
{
    return currentIndex_;
}

void VerticalButtonList::LeftSliderLock(bool flg)
{ 
    for (auto button : buttons_)
    {
        //ボタンがslider型なら実行
        if (ButtonSlider* slider = dynamic_cast<ButtonSlider*>(button)) {
            slider->IsLoakLeft(flg);
        }
    }
}

void VerticalButtonList::RightSliderLock(bool flg)
{
    for (auto button : buttons_)
    {
        //ボタンがslider型なら実行
        if (ButtonSlider* slider = dynamic_cast<ButtonSlider*>(button)) {
            slider->IsLoakRight(flg);
        }
    }
}

float VerticalButtonList::FillAmouts()
{
    float allFill = 0.0f;
    for (auto button : buttons_)
    {
        //ボタンがslider型なら実行
        if (ButtonSlider* slider = dynamic_cast<ButtonSlider*>(button)) {
            allFill += slider->FillAmount();
        }
    }
    return allFill;
}

void VerticalButtonList::Select()
{
    int increment = 0;
    if (InputSystem::MenuUp())increment--;
    if (InputSystem::MenuDown())increment++;
    //入力が無ければ切り替えしない
    if (increment == 0)
    {
        impulse_ = false;
        return;
    }
    if (impulse_)return;
    impulse_ = true;

    //1つ前のボタンを選択解除
    buttons_[currentIndex_]->OnDeSelect();
    currentIndex_ = (currentIndex_ + increment + buttons_.size()) % buttons_.size();
    buttons_[currentIndex_]->OnSelect();
    SoundManager::PlaySE(Sound::MenuSelect);
}

void VerticalButtonList::Confirm()
{
    if (!InputSystem::ButtonTrigger(InputSystem::Button::A))return;
    buttons_[currentIndex_]->OnConfirm();
    SoundManager::PlaySE(Sound::MenuConfirm);
}
