#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <unordered_map>
#include <string>
#include "SceneData.h"
class IScene;

// シーン管理クラス
class SceneManager {
public:
    SceneManager();
    ~SceneManager();
    void Update(float delta_time);
    void Draw() const;
    void End();
    void Add(const SceneIndex& name, IScene* scene);
    void Change(const SceneIndex& name);
    void Debug(float delta_time);
    void Clear();
    //強制終了
    bool IsRunning();
    // コピー禁止
    SceneManager(const SceneManager& other) = delete;
    SceneManager& operator = (const SceneManager& other) = delete;
    //値受け渡し
    SceneData CurrentSceneData();

private:
    // メイン更新
    void MainUpdate(float delta_time);

private:
    // シーン
    std::unordered_map<SceneIndex, IScene*> scenes_;

    // 現在のシーン
    IScene* currentScene_;
    // シーンの名前
    SceneIndex sceneName_;
    // 前回のシーンの名前
    SceneIndex recSceneName_;
    // シーンを切り替えるか
    bool changeScene_{ false };
    // サブシーンか
    bool isSubScene_{ false };

};

#endif
