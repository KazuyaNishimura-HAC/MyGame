#ifndef SCENE_DATA_H_
#define SCENE_DATA_H_

struct SceneData
{
    SceneData() {};
    SceneData(int stageID,int gameMode,int enemyLevel)
    {
        stage = stageID;
        mode = gameMode;
        level = enemyLevel;
    };
    //ステージID（デフォルト0）
    int stage{ 0 };
    //CPUかローカルか(デフォルト0)
    int mode{ 0 };
    //敵の強さ（デフォルト0）
    int level{ 0 };
};

enum class SceneIndex
{
    NullScene,
    TitleScene,
    LoadScene,
    GamePlayScene,
    ResultScene,
    PauseScene
};
#endif
