#include "HorizontalButtonList.h"
#include "Button.h"
#include "../../GameSystem/InputSystem/InputSystem.h"
#include "../../Sound/SoundManager.h"

HorizontalButtonList::HorizontalButtonList(GSvector2 position, int defalutIndex, float buttonDistance)
    :GUI(position), defaultIndex_{ defalutIndex }, buttonDistance_{ buttonDistance }
{
}

HorizontalButtonList::~HorizontalButtonList()
{
    for (auto button : buttons_)
    {
        delete button;
    }
    buttons_.clear();
}

void HorizontalButtonList::AddButton(Button* newButton , GSvector2 offset)
{
    newButton->SetPosition({ (position_.x + buttons_.size() * buttonDistance_) + offset.x,position_.y + offset.y }, 48);
    buttons_.push_back(newButton);
    //1つ目のボタンは選択
    if (buttons_.size() > 1)return;
    newButton->OnSelect();
}

void HorizontalButtonList::Update(float deltaTime)
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
    //キャンセル時
    /*if (!InputSystem::ButtonTrigger(InputSystem::Button::B))return;
    buttons_[currentIndex_]->OnDeSelect();
    buttons_[defaultIndex_]->OnSelect();
    buttons_[defaultIndex_]->OnConfirm();
    currentIndex_ = defaultIndex_;*/
}

void HorizontalButtonList::Draw() const
{
    if (!enable_)return;
    for (auto button : buttons_)
    {
        button->Draw();
    }
}

void HorizontalButtonList::Enable(bool enable)
{
    enabledFrameWait_ = true;
    if (!enable_ && enable)SoundManager::PlaySE(Sound::MenuPop);
    GUI::Enable(enable);
}

int HorizontalButtonList::SelectIndex()
{
    return currentIndex_;
}

void HorizontalButtonList::Select()
{
    int increment = 0;
    if (InputSystem::MenuLeft())increment--;
    if (InputSystem::MenuRight())increment++;
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

void HorizontalButtonList::Confirm()
{
    if (!InputSystem::ButtonTrigger(InputSystem::Button::A))return;
    buttons_[currentIndex_]->OnConfirm();
    SoundManager::PlaySE(Sound::MenuConfirm);
}
