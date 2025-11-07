#include "GamePlayScene.h"
#include "../../World/World.h"
#include "../../AssetID/Assets.h"
#include "../../GameSystem/InputSystem/InputSystem.h"
#include "../../Actor/Player/Player.h"
#include "../../Actor/Enemy/Enemy.h"
#include "../../Actor/Enemy/Default/DefaultEnemy.h"
#include "../../GameSystem/Camera/DebugCamera.h"
#include "../../GameSystem/Field/FieldActor.h"
#include "../../GameSystem/Field/Field.h"
//動作確認用
#include "../../UI/Image.h"
// 開始
void GamePlayScene::Start() {
    world_.AddPlayer(new Player(&world_,{-50,0,0},Status(60, 10)));
    world_.AddCharactor(new DefaultEnemy(&world_, { 15,0,5 }));
    world_.AddCharactor(new DefaultEnemy(&world_, { 15,0,-5 }));
    world_.AddCharactor(new DefaultEnemy(&world_, { 5,0,0 },Status(120, 30)));
    world_.AddCamera(new Camera(&world_));
    world_.AddField(new FieldActor({0,0,0},Model::DefaultMap,Model::MapCollide));
    /*world_.AddField(new Field({ -20,0,6 },{ 120,10,1 }));
    world_.AddField(new Field({ -30,0,-6 }, { 100,10,1 }));*/
    //テスト
    world_.AddField(new Field({ -30,0,6 }, { 120,10,1 }));
    world_.AddField(new Field({ -30,0,-6 }, { 120,10,1 }));
    world_.AddField(new Field({ -80,0,0 }, { 1,10,30 }));
    world_.AddField(new Field({ 18,0,0 }, { 1,10,30 }));

    debugCamera_ = new DebugCamera(&world_);
    world_.Start();
}

// 更新
void GamePlayScene::Update(float delta_time) {
    world_.Update(delta_time);
    if (world_.IsEnd()) {
        sceneEnd_ = true;
    }
}
// 描画
void GamePlayScene::Draw() const {

    world_.Draw();
}

// 終了しているか
bool GamePlayScene::IsEnd() const {
    return sceneEnd_;
}

// 次のシーンを返す
SceneIndex GamePlayScene::Next() const {
    return SceneIndex::ResultScene;
}

// 終了
void GamePlayScene::End() {
    world_.Clear();
    delete debugCamera_;
    debugCamera_ = nullptr;
    sceneEnd_ = false;
}

bool GamePlayScene::IsRunning()
{
    return false;
}

//前のシーンのデータを取得
void GamePlayScene::SetSceneData(SceneData data)
{
}

void GamePlayScene::Debug(float delta_time)
{
    world_.Debug(delta_time);
    debugCamera_->Update(delta_time);
}