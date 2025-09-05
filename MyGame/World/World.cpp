﻿#include "World.h"
#include "../Actor/Actor.h"
#include "../Actor/Player/Player.h"
#include "../GameSystem/InputSystem/InputSystem.h"
#include "../UI/GUI.h"
#include "../GameSystem/Event/Event.h"
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
    cameraManager_.Update(deltaTime);
    // エフェクトの更新処理
    gsUpdateEffect(deltaTime);
    
}

void World::Draw() const
{
    for (auto camera : cameraManager_.GetCameras()) {
        //バッファクリア（色と深度）
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    fieldManager_.Clear();
    actorManager_.Clear();
    eventManager_.Clear();
    guiManager_.Clear();
    cameraManager_.Clear();
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
    //Back+Xでデバック表示切替
    if (InputSystem::DebugInput()) {
        isDebug_ = !isDebug_;
    }

    if (!isDebug_) return;
    actorManager_.Debug(deltaTime);
    cameraManager_.Debug();
    guiManager_.Debug();
}

bool World::IsDebug()
{
    return isDebug_;
}

void World::Message(EventMessage message)
{
    switch (message) {
    case EventMessage::GameStart:
        break;
    case EventMessage::GameEnd:
        break;
    default:
        break;
    }
}
