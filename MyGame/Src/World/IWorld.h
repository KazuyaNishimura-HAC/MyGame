#ifndef I_WORLD_H_
#define I_WORLD_H_

#include <string>
#include <GStransform.h>
#include "../GameSystem/Time.h"
#include "../GameSystem/Camera/CameraController.h"
#include <vector>
#include <list>

class Actor;
class GUI;
class Camera;
class Player;
class FieldActor;
class FieldManager;
class Event;
class CameraController;
class TimeLine;

enum class EventMessage
{
    GameStart,
    GameEnd,
};

class IWorld
{
public:
    virtual ~IWorld() = default;

    virtual Player* GetPlayer() = 0;
    virtual Actor* GetActor(std::string name) = 0;
    virtual Camera* GetCamera(float id = 0) = 0;
    virtual CameraController* GetCameraController(CameraController::Priority p) = 0;
    virtual int GetCameraCount() = 0;

    virtual void AddActor(Actor* actor) = 0;
    virtual void AddGUI(GUI* gui) = 0;
    virtual void AddCameraGUI(GUI* gui,int indep) = 0;
    virtual void AddField(FieldActor* field) = 0;
    virtual void AddEvent(Event* newEvent) {};
    virtual void AddCamera(Camera* camera) = 0;
    virtual void AddCameraController(CameraController* controller) = 0;

    virtual void SetTimeScale(TimeScale timeScale) = 0;

    virtual FieldManager& Fields() = 0;
    virtual TimeLine& GetTimeLine() = 0;

    virtual void IsEnd(bool end) = 0;
    virtual bool IsEnd() = 0;

    virtual void IsStart(bool end) = 0;
    virtual bool IsStart() = 0;

    virtual void Timer(bool flg) = 0;
    virtual bool Timer() = 0;

    virtual bool IsDebug() = 0;

    virtual void Message(EventMessage message) = 0;
    
};

#endif
