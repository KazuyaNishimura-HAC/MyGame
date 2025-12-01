#ifndef GAME_PLAY_SCENE_H_
#define GAME_PLAY_SCENE_H_

#include "../IScene.h"
#include "../../World/World.h"
#include "../SceneManager.h"
#include <gslib.h>

class DebugCamera;

// プレイ中シーン
class GamePlayScene : public IScene {
public:
    // 開始
    virtual void Start() override;
    // 更新
    virtual void Update(float delta_time) override;
    // 描画
    virtual void Draw() const override;
    // 終了しているか
    virtual bool IsEnd() const override;
    // 次のシーンを返す
    virtual SceneIndex Next() const override;
    // 終了
    virtual void End() override;
    //実行中か
    virtual bool IsRunning()override;

    virtual void SetSceneData(SceneData data) override;
    virtual void Debug(float delta_time)override;
private:

    void InitialSettings();
    void AddFields();
    World world_;

    DebugCamera* debugCamera_{ nullptr };
};

#endif
