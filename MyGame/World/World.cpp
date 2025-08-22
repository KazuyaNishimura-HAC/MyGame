#include "World.h"
#include "../Actor/Actor.h"
#include "../GameSystem/InputSystem/InputSystem.h"
#include "../UI/GUI.h"
#include "../GameSystem/Event/EventManager.h"
#include "../AssetID/SkyBox.h"
#include <imgui/imgui.h>
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
    gsLoadTexture(SkyBox::GamePlay, "Assets/SkyBox/default.dds");
}

void World::Update(float deltaTime)
{
#if _DEBUG
    if (!debug_ && InputSystem::DebugInput()) {
        debug_ = true;
    }
#endif
    fieldManager_.Update(deltaTime);
    actorManager_.Update(deltaTime);
    actorManager_.LateUpdate(deltaTime);
    eventManager_.Update(time_.GameDeltaTime());
    guiManager_.Update(deltaTime, time_.GameDeltaTime());
    fieldManager_.Remove();
    actorManager_.Remove();
    eventManager_.Remove();
    guiManager_.Remove();
    //当たり判定
    actorManager_.Collide();
    eventManager_.Collide();
    time_.Update(deltaTime);
    for (auto camera : cameras_) camera->Update(deltaTime);
    // エフェクトの更新処理
    gsUpdateEffect(deltaTime);
    Debug(deltaTime);
}

void World::Draw() const
{
    for (auto camera : cameras_) {
        camera->Draw();
        gsDrawSkyboxCubemap(SkyBox::GamePlay);
        fieldManager_.Draw(camera);
        actorManager_.Draw();
        eventManager_.Draw();
        // エフェクトの描画
        gsDrawEffect();
    }
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
    isEnd_ = false;
    for (auto camera : cameras_) {
        delete camera;
    }
    cameras_.clear();
    fieldManager_.Clear();
    actorManager_.Clear();
    eventManager_.Clear();
    guiManager_.Clear();
    time_.Pause(false);
    isEnd_ = false;
    isStart_ = false;
    isTimer_ = true;
    //SoundManager::StopBGM();
}

void World::AddPlayer(Player* player)
{
    actorManager_.AddPlayer(player);
}

void World::AddActor(Actor* actor)
{
    actorManager_.AddActor(actor);
}

void World::AddField(FieldActor* field)
{
    return fieldManager_.AddField(field);
}

Player* World::GetPlayer()
{
    return actorManager_.GetPlayer();
}

ActorManager& World::GetActorManager()
{
    return actorManager_;
}

FieldManager& World::Fields()
{
    return fieldManager_;
}



Camera* World::GetCameras(float id)
{
    return cameras_[id];
}

int World::GetCameraCount()
{
    return cameras_.size();
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

void World::AddCameras(Camera* camera)
{
    cameras_.push_back(camera);
}



void World::SetTimeScale(TimeScale timeScale)
{
    time_.SetTimeScale(timeScale);
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

void World::Timer(bool flg)
{
    isTimer_ = flg;
}

bool World::Timer()
{
    return isTimer_;
}

void World::Debug(float deltaTime)
{

    if (!debug_) return;
    ImGui::Begin("WorldDebug");
    if (ImGui::Button("DrawGUI")) {
        draw_ = !draw_;
        guiManager_.Enable(draw_);
    }
    if (ImGui::Button("Close")) {
        debug_ = false;
    }
    ImGui::End();
}

bool World::IsDebug()
{
    return draw_;
}
