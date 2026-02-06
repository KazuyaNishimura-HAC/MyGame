#ifndef EFFECT_H_
#define EFFECT_H_

#include <gslib.h>
#include <GSeffect.h>
#include <GStransform.h>

struct EffectParam
{
    GSvector3 position{ 0,0,0 };
    GSvector3 rotation{ 0,0,0 };
    GSvector3 scale{ 1,1,1 };
    GScolor color{ 1,1,1,1 };
    float speed{ 1.0f };
    EffectParam(GSvector3 pos = { 0,0,0 }, GSvector3 rot = { 0,0,0 }, GSvector3 scale = { 1,1,1 }, GScolor color = { 1,1,1,1 },float speed = 1)
        :position{ pos }, rotation{ rot }, scale{ scale }, color{ color }, speed{ speed } {
    }
};

class Effect
{
public:
    enum ID
    {
        Slash,
        SkillSlash,
        Aura,
        Hit,
        GuardHit,
        ParryBreak,
        GroundDust,
        Exclamation,
        Confusion,
    };

    static GSuint CreateHandle(GSuint effectID) {

        return gsPlayEffectEx(effectID, nullptr);
    }
    //パラメータ設定
    static void SetParam(GSuint handle,const EffectParam& param) {
        GSmatrix4 matrix = GSmatrix4::TRS(param.position, GSquaternion::euler(param.rotation), param.scale);
        gsSetEffectMatrix(handle, &matrix);
        gsSetEffectSpeed(handle, param.speed);
        gsSetEffectColor(handle, &param.color);
    }
    //ローカル追従
    static void SetParam(GSuint handle, const EffectParam& param, const GStransform& transform) {
        GSmatrix4 matrix = GSmatrix4::TRS(param.position, GSquaternion::euler(param.rotation), param.scale);
        matrix *= transform.localToWorldMatrix();
        gsSetEffectMatrix(handle, &matrix);
        gsSetEffectSpeed(handle, param.speed);
        gsSetEffectColor(handle, &param.color);
    }
    static void Stop(GSuint handle) {
        gsStopEffect(handle);
    }

};
#endif
