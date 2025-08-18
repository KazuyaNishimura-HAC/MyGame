﻿#ifndef I_WORLD_H_
#define I_WORLD_H_

#include <string>
#include <GStransform.h>
#include "../GameSystem/Time.h"
#include <vector>
#include <list>

class Actor;
class GUI;
class Camera;
class Player;
class FieldActor;
class FieldManager;
class Event;
class Charactor;

class IWorld
{
public:
    virtual ~IWorld() = default;

    virtual Player* GetPlayer() = 0;
    virtual Camera* GetCameras(float index) = 0;
    virtual int GetCameraCount() = 0;

    virtual void AddActor(Actor* actor) = 0;
    virtual void AddGUI(GUI* gui) = 0;
    virtual void AddCameraGUI(GUI* gui,int indep) = 0;
    virtual void AddField(FieldActor* field) = 0;
    virtual void AddEvent(Event* newEvent) {};
    virtual void AddCameras(Camera* camera) = 0;

    virtual void SetTimeScale(TimeScale timeScale) = 0;

    virtual FieldManager& Fields() = 0;

    virtual void IsEnd(bool end) = 0;
    virtual bool IsEnd() = 0;

    virtual void IsStart(bool end) = 0;
    virtual bool IsStart() = 0;

    virtual void Timer(bool flg) = 0;
    virtual bool Timer() = 0;

    virtual bool IsDebug() = 0;
    
};

#endif
