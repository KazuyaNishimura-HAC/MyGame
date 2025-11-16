#ifndef EFFECT_H_
#define EFFECT_H_

#include <gslib.h>
#include <GSeffect.h>
#include <GStransform.h>

struct EffectParam
{
    GSuint handle{ 0 };
    GSvector3 position{ 0,0,0 };
    GSvector3 rotation{ 0,0,0 };
    GSvector3 scale{ 1,1,1 };
    GScolor color{ 1,1,1,1 };
    float speed{ 1.0f };
    EffectParam(GSuint id = 0, GSvector3 pos = { 0,0,0 }, GSvector3 rot = { 0,0,0 }, GSvector3 scale = { 1,1,1 }, GScolor color = { 1,1,1,1 },float speed = 1)
        :handle{ id }, position{ pos }, rotation{ rot }, scale{ scale }, color{ color }, speed{ speed } {
    }
};

class Effect
{
public:
    enum ID
    {
        Slash,
        Aura,
        Hit,
    };
    //座標を指定して再生
    static void SetEffectParam(const EffectParam& param) {
        GSmatrix4 matrix = GSmatrix4::TRS(param.position, GSquaternion::euler(param.rotation), param.scale);
        gsSetEffectMatrix(param.handle, &matrix);
        gsSetEffectSpeed(param.handle, param.speed);
        gsSetEffectColor(param.handle, &param.color);
    };
    //ローカル追従
    static void SetEffectParam(const EffectParam& param, const GStransform& transform) {
        GSmatrix4 matrix = GSmatrix4::TRS(param.position, GSquaternion::euler(param.rotation), param.scale);
        matrix *= transform.localToWorldMatrix();
        gsSetEffectMatrix(param.handle,&matrix);
        gsSetEffectSpeed(param.handle,param.speed);
        gsSetEffectColor(param.handle, &param.color);
    };

};
#endif
