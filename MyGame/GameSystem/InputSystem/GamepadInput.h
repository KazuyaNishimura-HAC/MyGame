#ifndef GAMEPAD_INPUT_H_
#define GAMEPAD_INPUT_H_

#include "IInputModule.h"

class GamepadInput :public IInputModule
{
public:
    GSvector2 LeftStick(int padID = 0)override;
    GSvector2 RightStick(int padID = 0)override;

    bool ButtonTrigger(int button, int padID = 0)override;
    bool ButtonIsPress(int button, int padID = 0)override;
    bool ButtonDetach(int button, int padID = 0)override;

    float LeftTriggerWeight(int padID = 0)override;
    float RightTriggerWeight(int padID = 0)override;

    float LeftStickRotate()override;
    float RightStickRotate()override;
    int ConnectedCount()override;
};

#endif
