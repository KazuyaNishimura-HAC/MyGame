#ifndef NULL_INPUT_H_
#define NULL_INPUT_H_

#include "IInputModule.h"

class NullInput :public IInputModule
{
public:
    GSvector2 LeftStick(int padID = 0)override { return GSvector2::zero(); };
    GSvector2 RightStick(int padID = 0) override { return GSvector2::zero(); };

    bool ButtonTrigger(int button, int padID = 0)override { return false; };
    bool ButtonIsPress(int button, int padID = 0)override { return false; };
    bool ButtonDetach(int button, int padID = 0) override { return false; };

    float LeftTriggerWeight(int padID = 0) override { return 0; };
    float RightTriggerWeight(int padID = 0) override { return 0; };
    float LeftStickRotate()override { return 0; };
    float RightStickRotate()override { return 0; };
    int ConnectedCount()override { return 0; }
};

#endif
