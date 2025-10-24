#include "GamePlayScene.h"
#include "../../World/World.h"
#include "../../AssetID/Assets.h"
#include "../../GameSystem/InputSystem/InputSystem.h"
#include "../../Actor/Player/Player.h"
#include "../../Actor/Enemy/Enemy.h"
#include "../../GameSystem/Camera/DebugCamera.h"
#include "../../GameSystem/Field/FieldActor.h"
#include "../../GameSystem/Field/Field.h"
//動作確認用
#include "../../UI/Image.h"
// 開始
void GamePlayScene::Start() {
    
    //メッシュ読み込み
    gsLoadSkinMesh(Model::Player, "Assets/Model/Charactor/Player/Player.mshb");
    gsLoadSkinMesh(Model::Enemy, "Assets/Model/Charactor/Enemy/Enemy1.mshb");
    gsLoadMesh(Model::DefaultMap,"Assets/Model/Stage/Stage1.mshb");
    gsLoadMesh(Model::MapCollide, "Assets/Model/Stage/StageCollider.mshb");
    
    world_.AddPlayer(new Player(&world_));
    world_.AddActor(new Enemy(&world_,Model::Enemy,{0,0,-5}));
    world_.AddCamera(new Camera(&world_));
    
    
    world_.AddField(new FieldActor({0,0,0},Model::DefaultMap,Model::MapCollide));
    world_.AddField(new Field({5,0,0},{5,10,1}));
    //動作チェック用
    gsLoadTexture(Texture::MenuSliderBackGround, "Assets/Texture/Menu/SliderBackGround.png");
    gsLoadTexture(Texture::MenuSliderFill, "Assets/Texture/Menu/SliderFill.png");
    world_.AddGUI(new Image({ 200,200 }, Texture::MenuSliderBackGround));
    world_.AddGUI(new Image({ 200,400 }, Texture::MenuSliderFill));

    debugCamera_ = new DebugCamera(&world_);
    world_.Start();
}

// 更新
void GamePlayScene::Update(float delta_time) {
    world_.Update(delta_time);
}
// 描画
void GamePlayScene::Draw() const {

    world_.Draw();
}

// 終了しているか
bool GamePlayScene::IsEnd() const {
    return InputSystem::ButtonTrigger(InputSystem::Button::Y);
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