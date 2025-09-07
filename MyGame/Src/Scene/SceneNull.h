#ifndef SCENE_NULL_H_
#define SCENE_NULL_H_

#include "IScene.h"

// NullScene
class SceneNull : public IScene {
public:
    // 開始
    virtual void Start() override {}
    // 更新
    virtual void Update(float delta_time) override {}
    // 描画
    virtual void Draw() const override {}
    // 終了しているか
    virtual bool IsEnd() const override {
        return false;
    }
    // 次のシーンを返す
    virtual SceneIndex Next() const override {
        return SceneIndex::NullScene;
    }
    // 終了
    virtual void End() override {}
    //強制終了
    virtual bool IsRunning()override {
        return false;
    }
};

#endif
