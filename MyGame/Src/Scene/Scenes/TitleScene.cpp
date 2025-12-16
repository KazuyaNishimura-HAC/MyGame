#include "TitleScene.h"
#include "../../GameSystem/InputSystem/InputSystem.h"
#include "../../UI/Image.h"
#include "../../Sound/SoundManager.h"
// 開始
void TitleScene::Start() {
    gsLoadTexture(Texture::TitleBGImage, "Assets/Texture/Scene/TitleBGImage.png");
    bgImage_ = new Image({ Screen::HalfWidth,Screen::HalfHeight }, Texture::TitleBGImage);
    guiManager_.AddGUI(bgImage_);
	gsLoadTexture(Texture::TitleLogo, "Assets/Texture/Scene/Titlelogo.png");
	text_ = new Image({ Screen::HalfWidth,Screen::HalfHeight - 300 },Texture::TitleLogo,{0.75f,0.75f});
	guiManager_.AddGUI(text_);
    gsLoadTexture(Texture::PressButtonText, "Assets/Texture/TextImage/PressBButtonText.png");
    buttonText_ = new Image({ Screen::HalfWidth,Screen::ScreenHeight - 200  }, Texture::PressButtonText, { 0.25f,0.25f });
    guiManager_.AddGUI(buttonText_);
    
    gsLoadBGM(Sound::Title, "Assets/Sound/BGM/Title.ogg", TRUE);
    SoundManager::PlayBGM(Sound::Title);
}

// 更新
void TitleScene::Update(float delta_time) {
	guiManager_.Update(delta_time,delta_time);
}

// 描画
void TitleScene::Draw() const {
	guiManager_.Draw();
}

// 終了しているか
bool TitleScene::IsEnd() const {
	return InputSystem::ButtonTrigger(InputSystem::Button::B);
}

// 次のシーンを返す
SceneIndex TitleScene::Next() const {
	return SceneIndex::LoadScene;
}

// 終了
void TitleScene::End() {
	gsDeleteTexture(Texture::TitleLogo);
	sceneEnd_ = false;
	guiManager_.Clear();
}

void TitleScene::Debug(float delta_time)
{

}
