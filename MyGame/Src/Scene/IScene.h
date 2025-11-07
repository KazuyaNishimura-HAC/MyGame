#ifndef ISCENE_H_
#define ISCENE_H_

#include <string>
#include <gslib.h>
#include "SceneData.h"

// シーン抽象インターフェース
class IScene {
public:
    virtual ~IScene() = default;
    virtual void Start() = 0;
    virtual void Update(float delta_time) = 0;
    virtual void Draw() const = 0;
    virtual bool IsEnd() const = 0;
    // 次のシーン名を返す
    virtual SceneIndex Next() const = 0;
    virtual void End() = 0;
    //強制終了
    virtual bool IsRunning() = 0;
    //シーン間の値受け渡し
    virtual SceneData GetSceneData() { return SceneData(); };

    //必要な時のみoverride
    virtual void SetSceneData(SceneData data = {}) {};
    virtual void Debug(float delta_time) {};
protected:
    bool sceneEnd_{ false };
};

#endif
