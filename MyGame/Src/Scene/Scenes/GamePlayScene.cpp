#include "GamePlayScene.h"
#include "../../World/World.h"
#include "../../AssetID/Assets.h"
#include "../../GameSystem/InputSystem/InputSystem.h"
#include "../../Actor/Charactor/Player/Player.h"
#include "../../Actor/Charactor/Enemy/Enemy.h"
#include "../../Actor/Charactor/Enemy/SwordEnemy1/SwordEnemy1.h"
#include "../../Actor/Charactor/Enemy/Boss/Boss.h"
#include "../../GameSystem/Camera/DebugCamera.h"
#include "../../GameSystem/Field/FieldActor.h"
#include "../../GameSystem/Field/Field.h"
#include "../../GameSystem/BattleSystem/BattleManager.h"
//動作確認用
#include "../../UI/Image.h"
// 開始
void GamePlayScene::Start() {
    debugCamera_ = new DebugCamera(&world_);
    InitialSettings();
    //バトルマネージャを追加
    world_.AddBattleManager(new BattleManager(&world_));
    world_.Start();
}

// 更新
void GamePlayScene::Update(float delta_time) {
    world_.Update(delta_time);
    if (InputSystem::ButtonTrigger(InputSystem::Button::Start)) {
        world_.Message(EventMessage::GamePause);
    }
    if (InputSystem::ButtonDetach(InputSystem::Button::Start)) {
        world_.Message(EventMessage::PauseEnd);
    }
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

void GamePlayScene::InitialSettings()
{
    //カメラ追加
    world_.AddCamera(new Camera(&world_));
    //Actor生成
    AddActors();
    AddFields();
}

void GamePlayScene::AddActors()
{
    world_.AddPlayer(new Player(&world_, {}, { 0,90,0 }, Status{ 100, 10 }));
}

void GamePlayScene::AddFields()
{
    world_.AddField(new FieldActor({ 0,0,0 }, Model::DefaultMap, Model::MapCollide));
    //テスト
    world_.AddField(new Field({ -7,0,0 }, { 1,10,30 }));
    world_.AddField(new Field({ 5,0,6 }, { 30,10,2 }));
    world_.AddField(new Field({ 5,0,-6 },{ 30,10,2 }));

    world_.AddField(new Field({ 20,0,9 }, { 1.5,10,15 }));
    world_.AddField(new Field({ 20,0,-9 }, { 1.5,10,15 }));
    world_.AddField(new Field({ 48,0,8 }, { 1,10,13 }));
    world_.AddField(new Field({ 48,0,-8 }, { 1,10,13 }));
    world_.AddField(new Field({ 57,0,6 }, { 18,10,2 }));
    world_.AddField(new Field({ 57,0,-6 }, { 18,10,2 }));

    world_.AddField(new Field({ 66,0,9 }, { 1.5,10,15 }));
    world_.AddField(new Field({ 66,0,-9 }, { 1.5,10,15 }));
    world_.AddField(new Field({ 94,0,8 }, { 1,10,13 }));
    world_.AddField(new Field({ 94,0,-8 }, { 1,10,13 }));
    world_.AddField(new Field({ 103,0,6 }, { 18,10,2 }));
    world_.AddField(new Field({ 103,0,-6 }, { 18,10,2 }));

    world_.AddField(new Field({ 112,0,9 }, { 1.5,10,15 }));
    world_.AddField(new Field({ 112,0,-9 }, { 1.5,10,15 }));
    world_.AddField(new Field({ 140,0,8 }, { 1,10,13 }));
    world_.AddField(new Field({ 140,0,-8 }, { 1,10,13 }));
    world_.AddField(new Field({ 152,0,6 }, { 24,10,2 }));
    world_.AddField(new Field({ 152,0,-6 }, { 24,10,2 }));

    world_.AddField(new Field({ 164,0,9 }, { 1.5,10,15 }));
    world_.AddField(new Field({ 164,0,-9 }, { 1.5,10,15 }));
    world_.AddField(new Field({ 192,0,0 }, { 1,10,30 }));

    //縦線
    world_.AddField(new Field({ 60,0,14 }, { 300,10,2 }));
    world_.AddField(new Field({ 60,0,-14 }, { 300,10,2 }));
}
