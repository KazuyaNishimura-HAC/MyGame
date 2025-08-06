#ifndef I_INPUT_MODULE_H_
#define I_INPUT_MODULE_H_

#include <gslib.h>

class IInputModule
{
public:
    virtual void Update(float deltaTime) {};

    virtual GSvector2 LeftStick(int padID = 0) = 0;
    virtual GSvector2 RightStick(int padID = 0) = 0;

    virtual bool ButtonTrigger(int button, int padID = 0) = 0;
    virtual bool ButtonIsPress(int button, int padID = 0) = 0;
    virtual bool ButtonDetach(int button, int padID = 0) = 0;

    virtual float LeftTriggerWeight(int padID = 0) = 0;
    virtual float RightTriggerWeight(int padID = 0) = 0;
    virtual float LeftStickRotate() = 0;
    virtual float RightStickRotate() = 0;
    virtual int ConnectedCount() = 0;
};

#endif
