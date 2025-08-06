#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include "../IScene.h"
#include "../SceneManager.h"

// タイトルシーン
class TitleScene : public IScene {
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
};

#endif
