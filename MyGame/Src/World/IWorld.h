#ifndef I_WORLD_H_
#define I_WORLD_H_

#include <string>
#include <GStransform.h>
#include "../GameSystem/Time.h"
#include "../GameSystem/Camera/CameraController.h"
#include <vector>
#include <list>

class Player;
class Actor;
class Charactor;
class GUI;
class Camera;
class Player;
class FieldActor;
class Field;
class FieldManager;
class Event;
class CameraController;
class TimeLine;

enum class WorldMessage
{
    GameStart,
    GameEnd,
    GamePause,
    PauseEnd
};

class IWorld
{
public:
    virtual ~IWorld() = default;

    virtual Player* GetPlayer() = 0;
    virtual Actor* GetAllActor(std::string name) = 0;
    virtual Actor* GetActor(std::string name) = 0;
    virtual Charactor* GetCharactor(std::string name) = 0;
    virtual Camera* GetCamera(float id = 0) = 0;
    virtual CameraController* GetCameraController(CameraController::Priority p) = 0;
    virtual int GetCameraCount() = 0;

    virtual void AddPlayer(Player* player) = 0;
    virtual void AddActor(Actor* actor) = 0;
    virtual void AddCharactor(Charactor* charactor) = 0;
    virtual void AddGUI(GUI* gui) = 0;
    virtual void AddCameraGUI(GUI* gui,int indep) = 0;
    virtual void AddField(FieldActor* field) = 0;
    virtual void AddField(Field* field) = 0;
    virtual void AddEvent(Event* newEvent) {};
    virtual void AddCamera(Camera* camera) = 0;
    virtual void AddCameraController(CameraController* controller) = 0;

    virtual void SetTimeScale(TimeScale timeScale) = 0;
    virtual float DeltaTime() = 0;
    virtual bool IsTimeScaleDefault() = 0;

    virtual FieldManager& Fields() = 0;
    virtual TimeLine& GetTimeLine() = 0;

    virtual void IsEnd(bool end) = 0;
    virtual bool IsEnd() = 0;

    virtual void IsStart(bool end) = 0;
    virtual bool IsStart() = 0;

    virtual bool IsPause() = 0;

    virtual void Timer(bool flg) = 0;
    virtual bool Timer() = 0;

    virtual bool IsRunningEvent() = 0;
    virtual bool IsDebug() = 0;

    virtual void Message(WorldMessage message) = 0;
    
};

#endif
