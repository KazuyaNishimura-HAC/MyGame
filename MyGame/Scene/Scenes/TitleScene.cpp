#include "TitleScene.h"
#include "../../GameSystem/InputSystem/InputSystem.h"

// 開始
void TitleScene::Start() {

}

// 更新
void TitleScene::Update(float delta_time) {

}

// 描画
void TitleScene::Draw() const {
	gsDrawText("Title");
}

// 終了しているか
bool TitleScene::IsEnd() const {
	return InputSystem::ButtonTrigger(InputSystem::Button::Y);
}

// 次のシーンを返す
SceneIndex TitleScene::Next() const {
	return SceneIndex::GamePlayScene;
}

// 終了
void TitleScene::End() {

}

void TitleScene::Debug(float delta_time)
{

}
