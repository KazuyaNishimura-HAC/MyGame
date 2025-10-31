#ifndef WORLD_H_
#define WORLD_H_

#include "IWorld.h"
#include "../Actor/ActorManager.h"
#include "../UI/GUIManager.h"
#include "../Graphics/Mesh/MeshDrawer.h"
#include "../Scene/SceneData.h"
#include "../GameSystem/Field/FieldManager.h"
#include "../GameSystem/Event/EventManager.h"
#include "../GameSystem/Camera/CameraManager.h"
class GUI;
class Player;
class Event;
class Camera;
class CameraController;
class TimeLineEditor;

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
    void AddCharactor(Charactor* charactor)override;
    void AddField(FieldActor* field)override;
    void AddField(Field* field)override;
    void AddGUI(GUI* gui)override;
    void AddCameraGUI(GUI* gui,int indep)override;
    void AddEvent(Event* newEvent)override;
    void AddCamera(Camera* camera)override;
    void AddCameraController(CameraController* controller)override;

    Player* GetPlayer()override;
    Actor* GetAllActor(std::string name)override;
    Actor* GetActor(std::string name)override;
    Charactor* GetCharactor(std::string name)override;
    Camera* GetCamera(float id = 0)override;
    CameraController* GetCameraController(CameraController::Priority p)override;
    int GetCameraCount()override;

    ActorManager& GetActorManager();
    FieldManager& Fields()override;
    TimeLine& GetTimeLine()override;

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

    void Message(EventMessage message)override;

private:
    //管理マネージャー
    ActorManager actorManager_;
    GUIManager guiManager_;
    FieldManager fieldManager_;
    EventManager eventManager_;
    CameraManager cameraManager_;
    //エディター
    TimeLineEditor* timeLineEditor_{ nullptr };
    Time time_;
    bool draw_{ true };
    bool isDebug_{ false };
    //ゲーム終了フラグ
    bool isEnd_{ false };
    bool isStart_{ false };
    bool isTimer_{ true };
};

#endif
