#ifndef SOUND_MENU_H_
#define SOUND_MENU_H_

#include "Image.h"
#include "GUI.h"
#include "GUIManager.h"

class GUI;
class VerticalButtonList;

class SoundMenu : public GUI
{
public:
    SoundMenu();
    void Draw()const override;
    void Update(float deltaTime)override;
    void BeginSoundSetting();
    void EndSoundSetting();
    bool GameEnd();
private:
    void SoundSettings();
    VerticalButtonList* soundMenu_;
    GUIManager guiManager_;
    bool gameEnd_{ false };
};
#endif
