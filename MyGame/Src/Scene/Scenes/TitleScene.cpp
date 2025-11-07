#include "TitleScene.h"
#include "../../GameSystem/InputSystem/InputSystem.h"
#include "../../UI/Image.h"
// 開始
void TitleScene::Start() {
	gsLoadTexture(Texture::TitleText, "Assets/Texture/Scene/TitleText.png");
	text_ = new Image({ 150,50 },Texture::TitleText);
	guiManager_.AddGUI(text_);
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
	gsDeleteTexture(Texture::TitleText);
	sceneEnd_ = false;
	guiManager_.Clear();
}

void TitleScene::Debug(float delta_time)
{

}
