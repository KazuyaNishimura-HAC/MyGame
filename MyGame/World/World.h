#ifndef WORLD_H_
#define WORLD_H_

#include "IWorld.h"
#include "../Actor/ActorManager.h"
#include "../Actor/Player/Player.h"
#include "../UI/GUIManager.h"
#include "../Mesh/MeshDrawer.h"
#include "../Scene/SceneData.h"
#include "../GameSystem/Camera/Camera.h"
#include "../GameSystem/Field/FieldManager.h"
#include "../GameSystem/Event/EventManager.h"
#include <vector>
class GUI;
class Player;
class Event;
class Camera;

class World :public IWorld
{
public:
    World();
    ~World();

    void Start();
    void Update(float deltaTime);
    void Draw()const;
    void DrawGUI()const;
    void Clear();

    void AddPlayer(Player* player);
    void AddActor(Actor* actor)override;
    void AddField(FieldActor* field)override;
    void AddGUI(GUI* gui)override;
    void AddCameraGUI(GUI* gui,int indep)override;
    void AddEvent(Event* newEvent)override;
    void AddCameras(Camera* camera)override;

    Player* GetPlayer()override;
    Camera* GetCameras(float id)override;
    int GetCameraCount()override;

    ActorManager& GetActorManager();
    FieldManager& Fields()override;

    void SetTimeScale(TimeScale timeScale)override;

    void IsEnd(bool end)override;
    bool IsEnd()override;

    void IsStart(bool start)override;
    bool IsStart()override;

    void Timer(bool flg)override;
    bool Timer()override;

    //コピー禁止
    World(const World& other) = delete;
    World& operator=(const World& other) = delete;

    void Debug(float deltaTime);
    bool IsDebug()override;

private:
    std::vector<Camera*> cameras_;
    ActorManager actorManager_;
    GUIManager guiManager_;
    FieldManager fieldManager_;
    EventManager eventManager_;
    Time time_;
    bool draw_{ true };
    bool debug_{ false };
    //ゲーム終了フラグ
    bool isEnd_{ false };
    bool isStart_{ false };
    bool isTimer_{ true };
};

#endif
