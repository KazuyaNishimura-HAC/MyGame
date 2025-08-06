#ifndef ANIMATED_MESH_H_
#define ANIMATED_MESH_H_

#include <gslib.h>
#include <vector>
#include <list>
#include <functional>

#include "../../Mesh/MeshDrawer.h"

struct AnimationEvent
{
    AnimationEvent(GSuint motion, GSfloat time, std::function<void()>callback)
        :motion_{ motion }, time_{ time }, callback_{ callback }
    {}

    GSuint motion_;
    GSfloat time_;
    std::function<void()>callback_;
};
struct Motion
{
    GSuint clip_ = 0;
    GSfloat timer_ = 0;
    bool loop_ = false;
    float speed_ = 1;
    Motion(GSuint clip, GSfloat timer, bool loop)
    {
        clip_ = clip;
        timer_ = timer;
        loop_ = loop;
    }
};

class AnimatedMesh
{
public:
    AnimatedMesh(GSuint id, GSuint motion = 0, bool loop = true, GSuint numBones = 256);
    virtual ~AnimatedMesh();
    virtual void Update(float deltaTime);
    virtual void Draw()const;
    virtual void ChangeMotion(GSuint motion, bool loop = true, bool forceChange = false, float motionTime = 0, float lerpTime = 0);
    virtual void Transform(const GSmatrix4& matrix);
    int MotionClip()const;
    bool IsEndMotion()const;
    float MotionTime()const;
    void MotionTime(float time);
    float MotionEndTime()const;
    float MotionEndTime(GSuint motion)const;
    bool IsMotion(int motion);
    GSmatrix4 boneMatrices(int boneNo)const;

    //追加したインデックスを返す
    int AddEvent(GSuint motion, GSfloat time, std::function<void()>callback);
    void RemoveEvent(int index);

    virtual void Debug();

protected:
    void UpdateLerpTimer(float deltaTime);

    float UpdateMotionTimer(float deltaTime, Motion motion);
    float UpdateMotionTimer(float deltaTime, float timer, float motionSpeed, bool motionLoop, float motionEndTime);
    void UpdateEvent(float deltaTime);

    MeshDrawer mesh_;
    GSmatrix4 transform_;

    Motion curMotion_;
    Motion prevMotion_;

    GSfloat lerpTimer_;

    GSfloat constLerpTime{ 10 };

    std::vector<GSmatrix4>localBoneMatrices_;
    std::vector<GSmatrix4>boneMatrices_;

    std::vector<AnimationEvent*>events_;

    friend class DebugScene;
};

#endif
