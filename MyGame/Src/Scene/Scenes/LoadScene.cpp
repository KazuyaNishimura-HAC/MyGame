#include "LoadScene.h"
#include <GSgame.h>
#include <GSeffect.h>
#include "../../GameSystem/InputSystem/InputSystem.h"
#include "../../AssetID/Assets.h"
#include "../../UI/Image.h"
#include "../../UI/SimpleHorizontalGauge.h"
// 開始
void LoadScene::Start() {

    loadingGauge_ = new SimpleHorizontalGauge({ Screen::HalfWidth,Screen::ScreenHeight - 172 }, { 256,16 });
    loadingGauge_->FillAmount(0);
    loadCount_ = 0;
    guiManager_.AddGUI(loadingGauge_);
    gsLoadTexture(Texture::LoadingText, "Assets/Texture/Scene/LoadingText.png");
    text_ = new Image({ 150,50 }, Texture::LoadingText);
    guiManager_.AddGUI(text_);
    gslib::Game::run_thread([=] { LoadAssets(); });
    
}

// 更新
void LoadScene::Update(float delta_time) {
    float gaugeProgress = (float)loadCount_ / (float)totalAssetsCount_;
    loadingGauge_->FillAmount(gaugeProgress);
    guiManager_.Update(delta_time, delta_time);
    //読み込みが全て終わったら遷移
    if (loadCount_ >= totalAssetsCount_) LoadEnd();
}

// 描画
void LoadScene::Draw() const {
    guiManager_.Draw();
}

// 終了しているか
bool LoadScene::IsEnd() const {
    return sceneEnd_;
}

// 次のシーンを返す
SceneIndex LoadScene::Next() const {
    return SceneIndex::GamePlayScene;
}

// 終了
void LoadScene::End() {
    gsDeleteTexture(Texture::LoadingText);
    sceneEnd_ = false;
    guiManager_.Clear();
}

void LoadScene::Debug(float delta_time)
{
}

void LoadScene::LoadAssets() {
    //メッシュ読み込み
    gsLoadSkinMesh(Model::Player, "Assets/Model/Charactor/Player/Player.mshb");
    loadCount_++;
    gsLoadSkinMesh(Model::Enemy, "Assets/Model/Charactor/Enemy/Enemy1.mshb");
    loadCount_++;
    gsLoadMesh(Model::DefaultMap, "Assets/Model/Stage/Stage1.mshb");
    loadCount_++;
    gsLoadMesh(Model::MapCollide, "Assets/Model/Stage/StageCollider.mshb");
    loadCount_++;
    gsLoadSkinMesh(Model::Boss, "Assets/Model/Charactor/Boss/Boss.mshb");
    loadCount_++;
    gsLoadMesh(Model::GreatSword, "Assets/Model/Object/GreatSword.mshb");
    loadCount_++;
    //動作チェック用
    gsLoadTexture(Texture::MenuSliderBackGround, "Assets/Texture/Menu/SliderBackGround.png");
    loadCount_++;
    gsLoadTexture(Texture::MenuSliderFill, "Assets/Texture/Menu/SliderFill.png");
    loadCount_++;
    // エフェクトファイルの読み込み
    gsLoadEffect(Effect::Slash, "Assets/Effect/Slash/Slash02_white_gray.efkefc");
    loadCount_++;
    gsLoadEffect(Effect::Aura, "Assets/Effect/Aura02/Aura02_Purple.efkefc");
    loadCount_++;
}

void LoadScene::LoadEnd()
{
    sceneEnd_ = true;
}
