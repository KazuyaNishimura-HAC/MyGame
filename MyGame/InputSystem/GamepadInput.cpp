#include "GamepadInput.h"

static const GSushort buttons_[14]
{
    GS_XBOX_PAD_A,
    GS_XBOX_PAD_B,
    GS_XBOX_PAD_X,
    GS_XBOX_PAD_Y,
    GS_XBOX_PAD_UP,
    GS_XBOX_PAD_DOWN,
    GS_XBOX_PAD_LEFT,
    GS_XBOX_PAD_RIGHT,
    GS_XBOX_PAD_LEFT_SHOULDER,
    GS_XBOX_PAD_RIGHT_SHOULDER,
    GS_XBOX_PAD_LEFT_THUMB,
    GS_XBOX_PAD_RIGHT_THUMB,
    GS_XBOX_PAD_START,
    GS_XBOX_PAD_BACK
};

GSvector2 GamepadInput::LeftStick(int padID)
{
    GSvector2 inputVector;
    gsXBoxPadGetLeftAxis(padID, &inputVector);
    inputVector = GSvector2::clampMagnitude(inputVector, 1);
    return inputVector;
}

GSvector2 GamepadInput::RightStick(int padID)
{
    GSvector2 inputVector;
    gsXBoxPadGetRightAxis(padID, &inputVector);
    inputVector = GSvector2::clampMagnitude(inputVector, 1);
    return inputVector;
}

float GamepadInput::LeftStickRotate() {
    GSvector2 inputVector = LeftStick();
    //角度
    float angle;
    //斜辺計算
    float c = hypotf(inputVector.x, inputVector.y);
    //asin,acos計算
    float as, ac;
    as = asinf(inputVector.y / c);
    ac = acosf(inputVector.x / c);

    //180度以上の補正
    if (as < 0.0f) ac = (2.0f * 3.1415926535f) - ac;

    angle = ac * (180 / 3.1415926535f);

    return angle;
}

float GamepadInput::RightStickRotate() {
    GSvector2 inputVector = RightStick();
    //角度
    float angle;
    //斜辺計算
    float c = hypotf(inputVector.x, inputVector.y);
    //asin,acos計算
    float as, ac;
    as = asinf(inputVector.y / c);
    ac = acosf(inputVector.x / c);

    //180度以上の補正
    if (as < 0.0f) ac = (2.0f * 3.1415926535f) - ac;

    angle = ac * (180 / 3.1415926535f);

    return angle;
}

int GamepadInput::ConnectedCount()
{
    return gsXBoxGetPadCount();
}

bool GamepadInput::ButtonTrigger(int button, int padID)
{
    return gsXBoxPadButtonTrigger(padID, buttons_[button]);
}

bool GamepadInput::ButtonIsPress(int button, int padID)
{
    return gsXBoxPadButtonState(padID, buttons_[button]);
}

bool GamepadInput::ButtonDetach(int button, int padID)
{
    return gsXBoxPadButtonDetach(padID, buttons_[button]);
}

float GamepadInput::LeftTriggerWeight(int padID)
{
    return gsXBoxPadGetLeftTrigger(padID);
}

float GamepadInput::RightTriggerWeight(int padID)
{
    return gsXBoxPadGetRightTrigger(padID);
}
