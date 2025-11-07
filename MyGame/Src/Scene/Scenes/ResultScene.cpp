#include "ResultScene.h"
#include "../../GameSystem/InputSystem/InputSystem.h"
#include "../../UI/Image.h"

// 開始
void ResultScene::Start() {
	gsLoadTexture(Texture::ResultText, "Assets/Texture/Scene/ResultText.png");
	text_ = new Image({ 150,50 }, Texture::ResultText);
	guiManager_.AddGUI(text_);
}

// 更新
void ResultScene::Update(float delta_time) {
	guiManager_.Update(delta_time,delta_time);
}

// 描画
void ResultScene::Draw() const {
	guiManager_.Draw();
}

// 終了しているか
bool ResultScene::IsEnd() const {
	return InputSystem::ButtonTrigger(InputSystem::Button::B);
}

// 次のシーンを返す
SceneIndex ResultScene::Next() const {
	return SceneIndex::TitleScene;
}

// 終了
void ResultScene::End() {
	gsDeleteTexture(Texture::ResultText);
	sceneEnd_ = false;
	guiManager_.Clear();
}

void ResultScene::Debug(float delta_time)
{
}
