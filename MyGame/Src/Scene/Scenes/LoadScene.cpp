#include "LoadScene.h"
#include <GSgame.h>
#include <GSeffect.h>
#include "../../GameSystem/InputSystem/InputSystem.h"
#include "../../AssetID/Assets.h"
#include "../../UI/Image.h"
#include "../../UI/SimpleHorizontalGauge.h"
#include "../../Sound/SoundManager.h"
// 開始
void LoadScene::Start() {

    bgImage_ = new Image({ Screen::HalfWidth,Screen::HalfHeight }, Texture::TitleBGImage);
    guiManager_.AddGUI(bgImage_);

    loadingGauge_ = new SimpleHorizontalGauge({ Screen::ScreenWidth - 200,Screen::ScreenHeight - 172 }, { 256,16 });
    loadingGauge_->FillAmount(0);
    loadCount_ = 0;
    guiManager_.AddGUI(loadingGauge_);
    gsLoadTexture(Texture::LoadingText, "Assets/Texture/TextImage/LoadingText.png");
    text_ = new Image({ Screen::ScreenWidth - 200,Screen::ScreenHeight - 250 }, Texture::LoadingText,{0.25f,0.25f});
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
    SoundManager::StopBGM();
    guiManager_.Clear();
}

void LoadScene::Debug(float delta_time)
{
}

void LoadScene::LoadAssets() {
    //メッシュ読み込み8
    gsLoadTexture(SkyBox::GamePlay, "Assets/SkyBox/gameSkyBox.dds");
    loadCount_++;
    gsLoadSkinMesh(Model::Player, "Assets/Model/Charactor/Player/Player.mshb");
    loadCount_++;
    gsLoadSkinMesh(Model::Enemy, "Assets/Model/Charactor/Enemy/Enemy1.mshb");
    loadCount_++;
    gsLoadOctree(Model::DefaultMap, "Assets/Model/Stage/Tutorial/TutorialStage.oct");
    loadCount_++;
    gsLoadOctree(Model::MapCollide, "Assets/Model/Stage/Tutorial/TutorialStage.oct");
    loadCount_++;
    gsLoadSkinMesh(Model::Boss, "Assets/Model/Charactor/Boss/Boss.mshb");
    loadCount_++;
    gsLoadMesh(Model::GreatSword, "Assets/Model/Object/GreatSword.mshb");
    loadCount_++;
    gsLoadMesh(Model::Door, "Assets/Model/Object/RotateDoor.mshb");
    loadCount_++;
    //動作チェック用24
    gsLoadTexture(Texture::NumberText, "Assets/Texture/TextImage/NumberText.png");
    loadCount_++;
    gsLoadTexture(Texture::MenuSliderBackGround, "Assets/Texture/Menu/SliderBackGround.png");
    loadCount_++;
    gsLoadTexture(Texture::MenuSliderFill, "Assets/Texture/Menu/SliderFill.png");
    loadCount_++;
    gsLoadTexture(Texture::SoundAll, "Assets/Texture/Menu/Sound/All.png");
    loadCount_++;
    gsLoadTexture(Texture::SoundBGM, "Assets/Texture/Menu/Sound/BGM.png");
    loadCount_++;
    gsLoadTexture(Texture::SoundSE, "Assets/Texture/Menu/Sound/GameSE.png");
    loadCount_++;
    gsLoadTexture(Texture::BossMenuSliderBG, "Assets/Texture/GamePlay/BossSliderBG.png");
    loadCount_++;
    gsLoadTexture(Texture::BossSliderFill, "Assets/Texture/GamePlay/BossSliderFill.png");
    loadCount_++;

    gsLoadTexture(Texture::HitText, "Assets/Texture/TextImage/HitText.png");
    loadCount_++;
    gsLoadTexture(Texture::ResultText, "Assets/Texture/TextImage/RankText.png");
    loadCount_++;
    gsLoadTexture(Texture::RankText, "Assets/Texture/TextImage/RankText.png");
    loadCount_++;
    gsLoadTexture(Texture::RankS, "Assets/Texture/GamePlay/RankS.png");
    loadCount_++;
    gsLoadTexture(Texture::RankA, "Assets/Texture/GamePlay/RankA.png");
    loadCount_++;
    gsLoadTexture(Texture::RankB, "Assets/Texture/GamePlay/RankB.png");
    loadCount_++;
    gsLoadTexture(Texture::RankC, "Assets/Texture/GamePlay/RankC.png");
    loadCount_++;
    gsLoadTexture(Texture::MaxComboText, "Assets/Texture/TextImage/MaxComboText.png");
    loadCount_++;
    gsLoadTexture(Texture::ParryCountText, "Assets/Texture/TextImage/ParryCountText.png");
    loadCount_++;
    gsLoadTexture(Texture::TotalDamageText, "Assets/Texture/TextImage/TotalDamageText.png");
    loadCount_++;

    gsLoadTexture(Texture::HPGaugeBG, "Assets/Texture/GamePlay/HPGaugeBG.png");
    loadCount_++;
    gsLoadTexture(Texture::HPGaugeFill, "Assets/Texture/GamePlay/HPGaugeFill.png");
    loadCount_++;
    gsLoadTexture(Texture::SkillGaugeBG, "Assets/Texture/GamePlay/SkillGaugeBG.png");
    loadCount_++;
    gsLoadTexture(Texture::SkillGaugeFill, "Assets/Texture/GamePlay/SkillGaugeFill.png");
    loadCount_++;
    gsLoadTexture(Texture::UltimateIconBG, "Assets/Texture/GamePlay/UltmateIcon.png");
    loadCount_++;
    gsLoadTexture(Texture::UltimateIconFill, "Assets/Texture/GamePlay/UltmateIcon.png");
    loadCount_++;
    // エフェクトファイルの読み込み7
    gsLoadEffect(Effect::Slash, "Assets/Effect/Slash02/Slash02_white_gray.efkefc");
    loadCount_++;
    gsLoadEffect(Effect::SkillSlash, "Assets/Effect/Slash01/Slash01.efkefc");
    loadCount_++;
    gsLoadEffect(Effect::Aura, "Assets/Effect/Aura02/Aura02_Purple.efkefc");
    loadCount_++;
    gsLoadEffect(Effect::Hit, "Assets/Effect/Hit02/Hit02-random-direction.efkefc");
    loadCount_++;
    gsLoadEffect(Effect::GuardHit, "Assets/Effect/Guard/Guard03.efkefc");
    loadCount_++;
    gsLoadEffect(Effect::ParryBreak, "Assets/Effect/PickUpItem/PickUpItem03.efkefc");
    loadCount_++;
    gsLoadEffect(Effect::GroundDust, "Assets/Effect/GroundDust/GroundDustLarge.efkefc");
    loadCount_++;
    //サウンド7
    gsLoadBGM(Sound::Battle, "Assets/Sound/BGM/Battle.ogg", TRUE);
    loadCount_++;
    gsLoadBGM(Sound::BossBattle, "Assets/Sound/BGM/BossBattle.ogg", TRUE);
    loadCount_++;
    gsLoadSE(Sound::Attack, "Assets/Sound/SE/Attack.wav", 3, GWAVE_DEFAULT);
    loadCount_++;
    gsLoadSE(Sound::Footstep, "Assets/Sound/SE/Footstep.wav", 5, GWAVE_DEFAULT);
    loadCount_++;
    gsLoadSE(Sound::Guard, "Assets/Sound/SE/Guard.wav", 3, GWAVE_DEFAULT);
    loadCount_++;
    gsLoadSE(Sound::Hit, "Assets/Sound/SE/Hit.wav", 5, GWAVE_DEFAULT);
    loadCount_++;
    gsLoadSE(Sound::Parry, "Assets/Sound/SE/Parry.wav", 3, GWAVE_DEFAULT);
    loadCount_++;
}

void LoadScene::LoadEnd()
{
    sceneEnd_ = true;
}
