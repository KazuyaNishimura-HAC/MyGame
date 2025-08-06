#include "TitleScene.h"

// 開始
void TitleScene::Start() {

}

// 更新
void TitleScene::Update(float delta_time) {

}

// 描画
void TitleScene::Draw() const {
}

// 終了しているか
bool TitleScene::IsEnd() const {
	return false;
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
