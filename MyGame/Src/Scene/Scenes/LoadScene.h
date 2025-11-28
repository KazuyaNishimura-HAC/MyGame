#ifndef LOAD_SCENE_H_
#define LOAD_SCENE_H_

#include "../IScene.h"
#include "../../UI/GUIManager.h"

#include <vector>

class Image;
class SimpleHorizontalGauge;

// GamePlaySceneのロードシーン
class LoadScene : public IScene {
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
    //強制終了
    virtual bool IsRunning()override {
        return false;
    }
    virtual void Debug(float delta_time)override;

private:
    // 素材の読み込み関数
    void LoadAssets();
    void LoadEnd();
    int loadCount_{ 0 };
    int totalAssetsCount_{ 23 };
    SimpleHorizontalGauge* loadingGauge_;
    GUIManager guiManager_;
    Image* text_{ nullptr };
};

#endif
