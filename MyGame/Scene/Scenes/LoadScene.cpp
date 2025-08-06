#include "LoadScene.h"
#include <GSgame.h>

// 開始
void LoadScene::Start() {
    gslib::Game::run_thread([=] {Load(); });
}

// 更新
void LoadScene::Update(float delta_time) {
}

// 描画
void LoadScene::Draw() const {
}

// 終了しているか
bool LoadScene::IsEnd() const {
    return false;
}

// 次のシーンを返す
SceneIndex LoadScene::Next() const {
    return SceneIndex::GamePlayScene;
}

// 終了
void LoadScene::End() {
}

void LoadScene::Debug(float delta_time)
{
}

void LoadScene::Load() {
}
