﻿#include "GamePlayScene.h"
#include "../../World/World.h"
#include "../../AssetID/Assets.h"
#include "../../GameSystem/InputSystem/InputSystem.h"
#include "../../Actor/Player/Player.h"
#include "../../GameSystem/Camera/DebugCamera.h"

//動作確認用
#include "../../UI/Image.h"

// 開始
void GamePlayScene::Start() {
    
    //メッシュ読み込み
    gsLoadSkinMesh(Model::Player, "Assets/Model/Charactor/Player/Player.mshb");
    gsLoadMesh(Model::DefaultMap,"Assets/Model/Stage/TestPlane.mshb");
    
    world_.AddPlayer(new Player(&world_));
    world_.AddCamera(new Camera(&world_));
    
    
    world_.AddField(new FieldActor({0,0,0},Model::DefaultMap,Model::DefaultMap));
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
    debugCamera_->Draw();
    //draw_grid3D();
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

void GamePlayScene::draw_grid3D()const 
{
    //ライティング無効
    glDisable(GL_LIGHTING);
    // デプステスト無効 
    glDisable(GL_DEPTH_TEST);
    for (float g = -100.0f; g <= 100.0f; g += 1.0f) {
        // xz平面
        glColor3f(0.3f, 0.0f, 0.0f);	// 茶色
        glBegin(GL_LINES);
        glVertex3f(g, 0.0f, -100.0f);
        glVertex3f(g, 0.0f, 100.0f);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(-100.0f, 0.0f, g);
        glVertex3f(100.0f, 0.0f, g);
        glEnd();
        // xy平面
        glColor3f(0.2f, 0.2f, 0.2f);	// グレー
        glBegin(GL_LINES);
        glVertex3f(g, -100.0f, 0.0f);
        glVertex3f(g, 100.0f, 0.0f);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(-100.0f, g, 0.0f);
        glVertex3f(100.0f, g, 0.0f);
        glEnd();

    }
    // ｘ軸を描画
    glColor3f(1.0f, 0.0f, 0.0f);	// 赤色
    glBegin(GL_LINES);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    glEnd();
    // ｙ軸を描画
    glColor3f(0.0f, 1.0f, 0.0f);	// 緑色
    glBegin(GL_LINES);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    glEnd();
    // z軸を描画
    glColor3f(0.0f, 0.0f, 1.0f);	// 青色
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();
    // 白に戻す
    glColor3f(1.0f, 1.0f, 1.0f);
    //ライティング有効
    glEnable(GL_LIGHTING);
    // デプステスト有効
    glEnable(GL_DEPTH_TEST);
}