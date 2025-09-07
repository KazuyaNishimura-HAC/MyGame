#include "ResultScene.h"
#include "../../GameSystem/InputSystem/InputSystem.h"

// 開始
void ResultScene::Start() {

}

// 更新
void ResultScene::Update(float delta_time) {

}

// 描画
void ResultScene::Draw() const {
	gsDrawText("Result");
}

// 終了しているか
bool ResultScene::IsEnd() const {
	return InputSystem::ButtonTrigger(InputSystem::Button::Y);
}

// 次のシーンを返す
SceneIndex ResultScene::Next() const {
	return SceneIndex::TitleScene;
}

// 終了
void ResultScene::End() {
}

void ResultScene::Debug(float delta_time)
{
}
