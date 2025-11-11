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
    EffectParam(GSuint id = 0, GSvector3 pos = { 0,0,0 }, GSvector3 rot = { 0,0,0 }, GSvector3 scale = { 1,1,1 })
        :handle{ id }, position{ pos }, rotation{ rot }, scale{ scale } {
    }
};

class Effect
{
public:
    enum
    {
        Slash,
        Slash2
    };
    //座標を指定して再生
    static void PlayEffect(EffectParam param) {
        GSmatrix4 matrix = GSmatrix4::TRS(param.position, GSquaternion::euler(param.rotation), param.scale);
        gsPlayEffectEx(param.handle, &matrix);
    };
    //ローカル追従
    static void PlayEffect(EffectParam param, const GStransform& transform) {
        GSmatrix4 matrix = GSmatrix4::TRS(param.position, GSquaternion::euler(param.rotation), param.scale);
        matrix *= transform.localToWorldMatrix();
        gsPlayEffectEx(param.handle, &matrix);
    };
};
#endif
