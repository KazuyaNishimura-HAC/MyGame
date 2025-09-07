#include "SoundManager.h"
#include <gslib.h>
#include <GSmath.h>


static float masterVol_{ 1 };
static float bgmVol_{ 0.5f };
static float seVol_[2]{ 1,1 };
static float seAll_{ 0.5f };

void SoundManager::PlayBGM(Sound::BGM bgmType)
{
    if (gsIsPlayBGM())return;
    gsPlayBGM(bgmType);
}

void SoundManager::StopBGM()
{
    gsStopBGM();
}

void SoundManager::PlaySE(Sound::SE seType)
{
    gsPlaySE(seType);
}

void SoundManager::StopSE(Sound::SE seType)
{
    gsStopSE(seType);
}

void SoundManager::PlayRandomSE(Sound::SE begin, Sound::SE end)
{
    PlaySE(gsRand(begin, end));
}

void SoundManager::StopAll()
{
    gsStopSound();
}

void SoundManager::SetMasterVolume(float volume)
{
    gsSetPrimaryVolume(volume);
    masterVol_ = volume;
}

void SoundManager::SetBGMVolume(float volume)
{
    gsSetVolumeBGM(volume);
    bgmVol_ = volume;
}

void SoundManager::SetSEVolume(Sound::SEGroup group, float volume)
{
    for (int i = Sound::GroupBegin(group); i <= Sound::GroupEnd(group); i++)
    {
        gsSetVolumeSE(i, volume);
    }
    seVol_[group] = volume;
}

void SoundManager::SetAllSEVolume(float volume)
{
    for (int i = Sound::SE::GetSEStart; i < Sound::SE::GetSEEnd; i++) {
        gsSetVolumeSE(i,volume);
    }
    seAll_ = volume;

}

float SoundManager::GetMasterVolume()
{
    return masterVol_;
}

float SoundManager::GetBGMVolume()
{
    return bgmVol_;
}

float SoundManager::GetSEVolume(Sound::SEGroup group)
{
    return seVol_[group];
}

float SoundManager::GetSEAllVolume()
{
    return seAll_;
}

void SoundManager::PlaySE(int seType)
{
    gsPlaySE(seType);
}
