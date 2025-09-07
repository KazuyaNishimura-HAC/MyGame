#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_

#include "Sound.h"

class SoundManager
{
public:
    static void PlayBGM(Sound::BGM bgmType);
    static void StopBGM();
    static void PlaySE(Sound::SE seType);
    static void StopSE(Sound::SE seType);
    static void PlayRandomSE(Sound::SE begin, Sound::SE end);
    static void StopAll();

    /// <summary>
    /// 0=無音～1=デフォルト
    /// </summary>
    static void SetMasterVolume(float volume);
    /// <summary>
    /// 0=無音～1=デフォルト
    /// </summary>
    /// <param name="volume"></param>
    static void SetBGMVolume(float volume);
    /// <summary>
    /// SEGroupの音量をセット 0=無音～1=デフォルト
    /// </summary>
    static void SetSEVolume(Sound::SEGroup group, float volume);
    /// <summary>
    /// 0=無音～1=デフォルト
    /// </summary>
    static void SetAllSEVolume(float volume);

    static float GetMasterVolume();
    static float GetBGMVolume();
    static float GetSEVolume(Sound::SEGroup group);
    static float GetSEAllVolume();

private:
    //ランダム再生用(int型)
    static void PlaySE(int seType);
};
#endif

