#include "VibrationManager.h"

VibrationManager::Vibration left_, right_;
VibrationManager::VibrationManager()
{
}

void VibrationManager::Update(float deltaTime)
{
    gsXBoxPadSetVibration(0, left_.Amount(), right_.Amount());
    left_.Update(deltaTime);
    right_.Update(deltaTime);
}

void VibrationManager::SetVibration(Vibration left, Vibration right)
{
    SetVibrationLeft(left);
    SetVibrationRight(right);
}

void VibrationManager::SetVibrationLeft(Vibration left)
{
    left_ = left;
}

void VibrationManager::SetVibrationRight(Vibration right)
{
    right_ = right;
}

void VibrationManager::Stop()
{
    gsXBoxPadSetVibration(0, 0, 0);
}

void VibrationManager::Vibration::Update(float deltaTime)
{
    //無限
    if (duration == 0)return;
    timer = MAX(timer - deltaTime, 0);
}

float VibrationManager::Vibration::Amount()const
{
    if (duration == 0)return 0;
    return LERP(timer / duration, end, begin);
}
