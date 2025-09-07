#include "SceneManager.h"
#include "SceneNull.h"
#include "../NameTag.h"
#include "string.h"

// nullシーン
static SceneNull s_SceneNull;

// コンストラクタ
SceneManager::SceneManager() :
    currentScene_{ &s_SceneNull }
{
}

// デストラクタ
SceneManager::~SceneManager() {
    Clear();
}

// 更新
void SceneManager::Update(float delta_time) {
    // シーンが終了しているか
    if (currentScene_->IsEnd()) {
        // シーンを変更
        Change(currentScene_->Next());
        return;
    }
    MainUpdate(delta_time);
}

// 描画
void SceneManager::Draw() const {
    // 現在のシーンを描画
    currentScene_->Draw();
}

// 終了
void SceneManager::End() {
    // 現在のシーンを終了
    currentScene_->End();
    // nullシーンにしておく
    currentScene_ = &s_SceneNull;
}

// シーンの追加
void SceneManager::Add(const SceneIndex& name, IScene* scene) {
    scenes_[name] = scene;
}

// シーンの変更
void SceneManager::Change(const SceneIndex& name) {
    SceneData data = CurrentSceneData();
    recSceneName_ = sceneName_;
    sceneName_ = name;
    // 現在のシーンを終了
    End();
    // 現在のシーンを変更
    currentScene_ = scenes_[name];
    currentScene_->SetSceneData(data);
    //データ受け渡し
    // 現在のシーンを開始
    currentScene_->Start();
}

void SceneManager::Debug(float delta_time)
{
    currentScene_->Debug(delta_time);
}

// シーンの消去
void SceneManager::Clear() {
    // 念のためシーンの終了を呼び出す
    End();
    // unordered_map内のシーンをすべて削除
    for (auto& pair : scenes_) {
        delete pair.second;
    }
    // unordered_mapを消去
    scenes_.clear();
}

bool SceneManager::IsRunning()
{
    return currentScene_->IsRunning();
}

SceneData SceneManager::CurrentSceneData()
{
    return currentScene_->GetSceneData();
}

void SceneManager::MainUpdate(float delta_time)
{
    currentScene_->Update(delta_time);
    if (currentScene_->IsEnd()) {
        Change(currentScene_->Next());
    }
}

