#ifndef INPUT_SYSTEM_H_
#define INPUT_SYSTEM_H_

#include "IInputModule.h"
#include <gslib.h>

class InputSystem
{
public:
    InputSystem();
    static void Initialize(IInputModule* module);

    enum class Button
    {
        A, B, X, Y,
        Up, Down, Left, Right,
        LShoulder, RShoulder,
        LThumb, RThumb,
        Start, Back
    };

    static GSvector2 LeftStick(int padID = 0);
    static GSvector2 RightStick(int padID = 0);
    static float LeftStickRotate();
    static float RightStickRotate();
    /// <summary>
    /// 押された瞬間を返す
    /// </summary>
    static bool ButtonTrigger(Button button, int padID = 0);
    /// <summary>
    /// 押されている間を返す
    /// </summary>
    static bool ButtonIsPress(Button button, int padID = 0);
    /// <summary>
    /// 離された瞬間を返す
    /// </summary>
    static bool ButtonDetach(Button button, int padID = 0);

    static float LeftTriggerWeight(int padID = 0);
    static float RightTriggerWeight(int padID = 0);

    //コントローラーの接続数を返却
    static int ConnectedCount();

    static bool MenuInput();
    /// <summary>
    /// 十字,左右スティックの入力の和を返す
    /// </summary>
    /// <returns></returns>
    static GSvector2 AllDirection();
    static bool MenuUp();
    static bool MenuDown();
    static bool MenuLeft();
    static bool MenuRight();

    static bool ForceQuit();

    //[デバッグ入力]
    static bool DebugInput();
    static GSvector3 DebugMove();
    static bool DebugCamera();
    static bool DebugCameraStop();
    static int DebugCameraMode();
    static bool DebugCameraBoost();
    static GSvector3 DebugTriAxisComposite();
    static GSvector3 DebugMouseDelta();
};

#endif
