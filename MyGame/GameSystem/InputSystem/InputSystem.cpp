#include "InputSystem.h"
#include "NullInput.h"


static IInputModule* inputModule_;
void InputSystem::Initialize(IInputModule* module)
{
    inputModule_ = module;
}

InputSystem::InputSystem()
{
    static NullInput nullInput;
    inputModule_ = &nullInput;
}

GSvector2 InputSystem::LeftStick(int padID)
{
    return inputModule_->LeftStick(padID);
}

GSvector2 InputSystem::RightStick(int padID)
{
    return inputModule_->RightStick(padID);
}

float InputSystem::LeftStickRotate()
{
    return inputModule_->LeftStickRotate();
}
float InputSystem::RightStickRotate()
{
    return inputModule_->RightStickRotate();
}

bool InputSystem::ButtonTrigger(Button button, int padID)
{
    return inputModule_->ButtonTrigger((int)button, padID);
}

bool InputSystem::ButtonIsPress(Button button, int padID)
{
    return inputModule_->ButtonIsPress((int)button, padID);
}

bool InputSystem::ButtonDetach(Button button, int padID)
{
    return inputModule_->ButtonDetach((int)button, padID);
}

float InputSystem::LeftTriggerWeight(int padID)
{
    return inputModule_->LeftTriggerWeight(padID);
}

float InputSystem::RightTriggerWeight(int padID)
{
    return inputModule_->RightTriggerWeight(padID);
}

int InputSystem::ConnectedCount()
{
    return inputModule_->ConnectedCount();
}

bool InputSystem::MenuInput()
{
    return ButtonTrigger(Button::Start);
}

GSvector2 InputSystem::AllDirection()
{
    GSvector2 arrow;
    if (ButtonIsPress(Button::Up)) arrow.y++;
    if (ButtonIsPress(Button::Down)) arrow.y--;
    if (ButtonIsPress(Button::Left)) arrow.x--;
    if (ButtonIsPress(Button::Right)) arrow.x++;
    GSvector2 stick = LeftStick() + RightStick();
    return arrow + stick;
}

bool InputSystem::MenuUp()
{
    return AllDirection().y > 0.5f;
}

bool InputSystem::MenuDown()
{
    return AllDirection().y < -0.5f;
}

bool InputSystem::MenuLeft()
{
    return AllDirection().x < -0.5f;
}

bool InputSystem::MenuRight()
{
    return AllDirection().x > 0.5f;
}

bool InputSystem::ForceQuit()
{
    return ButtonIsPress(Button::Start) && ButtonIsPress(Button::Back);
}

bool InputSystem::DebugInput()
{
    return ButtonIsPress(Button::Back) && ButtonTrigger(Button::X);
}

GSvector3 InputSystem::DebugMove()
{
    GSvector3 move;
    if (gsGetKeyState(GKEY_A))move.x++;
    if (gsGetKeyState(GKEY_D))move.x--;
    if (gsGetKeyState(GKEY_W))move.z++;
    if (gsGetKeyState(GKEY_S))move.z--;
    if (gsGetKeyState(GKEY_SPACE))move.y++;
    if (gsGetKeyState(GKEY_LCONTROL))move.y--;
    return move;
}

bool InputSystem::DebugCamera()
{
    return gsGetKeyTrigger(GKEY_P);
}

bool InputSystem::DebugCameraStop()
{
    return gsGetKeyTrigger(GKEY_LALT);
}

int InputSystem::DebugCameraMode()
{
    if (gsGetKeyTrigger(GKEY_Q))return 0;
    if (gsGetKeyTrigger(GKEY_E))return 1;
    return -1;
}

bool InputSystem::DebugCameraBoost()
{
    return gsGetKeyState(GKEY_LSHIFT);
}

GSvector3 InputSystem::DebugTriAxisComposite()
{
    GSvector3 comp;
    if (gsGetKeyState(GKEY_U))comp.x++;
    if (gsGetKeyState(GKEY_J))comp.x--;
    if (gsGetKeyState(GKEY_I))comp.y++;
    if (gsGetKeyState(GKEY_K))comp.y--;
    if (gsGetKeyState(GKEY_O))comp.z++;
    if (gsGetKeyState(GKEY_L))comp.z--;
    return comp;
}

GSvector3 InputSystem::DebugMouseDelta()
{
    int x{ 0 }, y{ 0 }, z{ 0 };
    gsGetMouseVelocity(&x, &y, &z);
    return GSvector3{ (float)x / -10.0f,(float)y / -10.0f,(float)z / -120.0f };
}
