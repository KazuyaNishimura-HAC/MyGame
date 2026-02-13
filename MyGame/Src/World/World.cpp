#include "World.h"
#include "../Actor/Actor.h"
#include "../Actor/Charactor/Player/Player.h"
#include "../GameSystem/InputSystem/InputSystem.h"
#include "../UI/GUI.h"
#include "../GameSystem/Event/Event.h"
#include "../AssetID/SkyBox.h"
#include "../Graphics/Shader/RenderTexture.h"
#include "../Graphics/Shader/RenderTextureID.h"
#include "../Graphics/Effect/PostEffect.h"
#include "../GameSystem/Field/Light.h"

#include "../GameSystem/Event/TimeLine/TimeLineEditor.h"
#include "../GameSystem/BattleSystem/BattleManager.h"
#include "../Sound/SoundManager.h"

#include <GSeffect.h>
#include <GSgame.h>

World::World()
{
}

World::~World()
{
    Clear();
}

void World::Start()
{
    time_ = Time{};
    GetTimeLine().SetIWorld(this);
    timeLineEditor_ = new TimeLineEditor(this,GetTimeLine());
    GetTimeLine().LoadFile();
    PostEffect::Instance().Load();
    light_ = new Light(this);
}

void World::Update(float deltaTime)
{
    time_.Update(deltaTime);
#if _DEBUG
    timeLineEditor_->DrawEditUI();
#endif

    GameUpdate(time_.GameDeltaTime());
    vibrationManager_.Update(deltaTime);
    guiManager_.Update(deltaTime, time_.GameDeltaTime());
    //当たり判定
    actorManager_.Collide();
    
    for (auto& chara : actorManager_.GetCharactorList()) {
        fieldManager_.CollideActor(chara->Transform());
    }
    if(GetCamera())fieldManager_.CollideCamera(GetCamera()->Transform(), cameraManager_.GetActiveController()->GetViewTarget());
    actorManager_.LateUpdate(time_.GameDeltaTime());
    eventManager_.Invoke();
    fieldManager_.Remove();
    actorManager_.Remove();
    eventManager_.Remove();
    guiManager_.Remove();

    if(!time_.IsPause())cameraManager_.Update(deltaTime);
}

void World::Draw() const
{
    
    for (auto camera : cameraManager_.GetCameras()) {
        RenderTexture::BeginRender(Rt::BaseScene);
        //バッファクリア（色と深度）
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        camera->Draw();
        gsDrawSkyboxCubemap(SkyBox::GamePlay);
        gsDrawOctree(Model::DefaultMap);
        light_->Draw();
        fieldManager_.Draw(camera);
        // シャドウマップの描画
        gsDrawShadowMap(shadow_map_callback, (void*)this);
        actorManager_.Draw();
        eventManager_.Draw();
        gsDrawEffect();
        RenderTexture::EndRender();

        //エフェクトブレンド
        PostEffect::Instance().BeginBlend();
            PostEffect::Instance().RadialBlur();
            PostEffect::Instance().Bloom();
            PostEffect::Instance().Vignette();
        PostEffect::Instance().EndBlend();
    }
    //ブレンド後のシーンを描画
    RenderTexture::BindRenderTexture(Rt::FinalScene, 0);
    RenderTexture::Draw(Rt::FinalScene);
    RenderTexture::UnBindRenderTexture(Rt::FinalScene, 0);
    //描画範囲を画面全体にリセット
    glViewport(0, 0, Screen::ScreenWidth, Screen::ScreenHeight);
    DrawGUI();
}

void World::DrawGUI() const
{
    guiManager_.Draw();
}

void World::Clear()
{
    delete timeLineEditor_;
    timeLineEditor_ = nullptr;
    delete light_;
    light_ = nullptr;
    fieldManager_.Clear();
    actorManager_.Clear();
    eventManager_.Clear();
    guiManager_.Clear();
    cameraManager_.Clear();
    time_.SetPause(false);
    isEnd_ = false;
    isStart_ = false;
    isTimer_ = true;
    gsStopAllEffects();
    PostEffect::Instance().Clear();
    SoundManager::StopBGM();
    SoundManager::StopAll();
}

void World::GameUpdate(float deltaTime)
{
    if (time_.IsPause()) return;
    fieldManager_.Update(deltaTime);
    actorManager_.Update(deltaTime);
    eventManager_.Update(deltaTime);
    gsUpdateEffect(deltaTime);
}

void World::AddPlayer(Player* player)
{
    actorManager_.AddPlayer(player);
}

void World::AddActor(Actor* actor)
{
    actorManager_.AddActor(actor);
}

void World::AddCharactor(Charactor* charactor)
{
    actorManager_.AddCharactor(charactor);
}

void World::AddField(FieldActor* field)
{
    return fieldManager_.AddField(field);
}

void World::AddField(Field* field)
{
    return fieldManager_.AddField(field);
}

Player* World::GetPlayer()
{
    return actorManager_.GetPlayer();
}

Actor* World::GetAllActor(std::string name)
{
    return actorManager_.GetAllActor(name);
}

Actor* World::GetActor(std::string name)
{
    return actorManager_.GetActor(name);
}

Charactor* World::GetCharactor(std::string name)
{
    return actorManager_.GetCharactor(name);
}

ActorManager& World::GetActorManager()
{
    return actorManager_;
}

FieldManager& World::Fields()
{
    return fieldManager_;
}

TimeLine& World::GetTimeLine()
{
    return eventManager_.GetTimeLine();
}

Camera* World::GetCamera(float id)
{
    return cameraManager_.GetCamera(id);
}

CameraController* World::GetCameraController(CameraController::Priority p)
{
    return nullptr;
}

int World::GetCameraCount()
{
    return cameraManager_.CameraCount();
}

void World::AddGUI(GUI* gui)
{
    guiManager_.AddGUI(gui);
}

void World::AddCameraGUI(GUI* gui,int indep)
{
    guiManager_.AddCameraGUI(gui, indep);
}

void World::AddEvent(Event* newEvent)
{
    eventManager_.AddEvent(newEvent);
}

void World::AddCamera(Camera* camera)
{
    cameraManager_.AddCamera(camera);
}

void World::AddCameraController(CameraController* controller)
{
    cameraManager_.AddController(controller);
}

void World::SetTimeScale(TimeScale timeScale)
{
    time_.SetTimeScale(timeScale);
}

float World::DeltaTime()
{
    return time_.DeltaTime();
}

bool World::IsTimeScaleDefault()
{
    return time_.IsTimeScaleDefault();
}

void World::IsEnd(bool end)
{
    isEnd_ = end;
}

bool World::IsEnd()
{
    return isEnd_;
}

void World::IsStart(bool start)
{
    isStart_ = start;
}

bool World::IsStart()
{
    return isStart_;
}

bool World::IsPause()
{
    return time_.IsPause();
}

void World::Timer(bool flg)
{
    isTimer_ = flg;
}

bool World::Timer()
{
    return isTimer_;
}

bool World::IsRunningEvent()
{
    return eventManager_.IsRunning();
}
// シャドウマップの描画用の関数
void World::shadow_map_callback(void* param, const GSmatrix4*, const GSmatrix4*)
{
    World* self = (World*)param;
    // シャドウマップにはアクターのみ描画
    self->actorManager_.ShadowDraw();
}

void World::Debug(float deltaTime)
{
    //Back+Xでデバック表示切替
    if (InputSystem::DebugInput()) {
        isDebug_ = !isDebug_;
    }
    ImGui::Begin("WorldGUI");
    ImGui::Value("FPS", 60 / deltaTime);
    ImGui::Value("TimeScale", time_.GetTimeScale());
    ImGui::Value("DeltaTime", time_.DeltaTime());
    ImGui::End();
    if (!isDebug_) return;
    actorManager_.Debug(deltaTime);
    cameraManager_.Debug();
    guiManager_.Debug();
    eventManager_.Debug();
    PostEffect::Instance().Debug();
}

bool World::IsDebug()
{
    return isDebug_;
}

void World::Message(WorldMessage message)
{
    switch (message) {
    case WorldMessage::GameStart:
        break;
    case WorldMessage::GameEnd:
        isEnd_ = true;
        break;
    case WorldMessage::GamePause:
        time_.SetPause(true);
        break;
    case WorldMessage::PauseEnd:
        time_.SetPause(false);
        break;
    case WorldMessage::GUIEnableTrue:
        guiManager_.Enable(true);
        break;
    case WorldMessage::GUIEnableFalse:
        guiManager_.Enable(false);
        break;
    case WorldMessage::ResultStart:
        guiManager_.Enable(false);
        break;
    default:
        break;
    }
}
