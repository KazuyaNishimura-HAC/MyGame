#ifndef VIBRATION_MANAGER_H_
#define VIBRATION_MANAGER_H_

#include <gslib.h>

class VibrationManager
{
public:
    struct Vibration
    {
        Vibration(float begin = 0, float duration = 0, float end = 0)
            :begin{ begin }, duration{ duration }, timer{ duration }, end{ end } {};
        void Update(float deltaTime);
        float Amount()const;
    private:
        float duration{ 0 };
        float begin{ 0 };
        float timer{ 0 };
        float end{ 0 };
    };

    VibrationManager();
    void Update(float deltaTime);
    static void SetVibration(Vibration left, Vibration right);
    static void SetVibrationLeft(Vibration left);
    static void SetVibrationRight(Vibration right);
    static void Stop();
};

#endif
