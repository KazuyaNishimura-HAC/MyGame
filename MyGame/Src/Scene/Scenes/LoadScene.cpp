#include "LoadScene.h"
#include <GSgame.h>
#include "../../GameSystem/InputSystem/InputSystem.h"

// 開始
void LoadScene::Start() {
    gslib::Game::run_thread([=] {Load(); });
}

// 更新
void LoadScene::Update(float delta_time) {
}

// 描画
void LoadScene::Draw() const {
    gsDrawText("Load");
}

// 終了しているか
bool LoadScene::IsEnd() const {
    return InputSystem::ButtonTrigger(InputSystem::Button::Y);
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
