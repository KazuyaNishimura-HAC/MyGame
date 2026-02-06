#include "AnimatedMesh.h"
#include <cmath>
#include <algorithm>
#include <imgui/imgui.h>

AnimatedMesh::AnimatedMesh(GSuint id, GSuint motion, bool loop, GSuint numBones)
    :mesh_{ id }, transform_{ GS_MATRIX4_IDENTITY },
    curMotion_{ motion,0,loop },
    prevMotion_{ motion,0,false },
    lerpTimer_{ 0 },
    localBoneMatrices_{ numBones },
    boneMatrices_{ numBones }
{

}

AnimatedMesh::~AnimatedMesh()
{
    for (auto animEvent : events_)
    {
        delete animEvent;
    }
    events_.clear();
}

void AnimatedMesh::Update(float deltaTime)
{
    UpdateEvent(deltaTime);

    curMotion_.timer_ = UpdateMotionTimer(deltaTime, curMotion_);
    prevMotion_.timer_ = UpdateMotionTimer(deltaTime, prevMotion_);

    UpdateLerpTimer(deltaTime);
}

void AnimatedMesh::Draw() const
{
    gsDisable(GS_CALC_SKELETON);
    //行列の適用
    gsBindSkeleton(mesh_.MeshID());
    gsSetMatrixSkeleton(boneMatrices_.data());
    mesh_.Draw(transform_);
    gsEnable(GS_CALC_SKELETON);
    
}

void AnimatedMesh::ChangeMotion(GSuint motion, bool loop, float motionSpeed, float motionTime, float lerpTime, bool forceChange)
{
    if (curMotion_.clip_ == motion && !forceChange && gsGetNumAnimations(mesh_.MeshID()) >= motion)return;

    if (lerpTimer_ > (constLerpTime * 0.5f))
    {
        prevMotion_ = curMotion_;
        lerpTimer_ = lerpTime;
    }

    curMotion_.clip_ = motion;
    curMotion_.timer_ = motionTime;
    curMotion_.loop_ = loop;
    curMotion_.speed_ = motionSpeed;
}

void AnimatedMesh::Transform(const GSmatrix4& matrix)
{
    transform_ = matrix;
    gsCalculateAnimationLerp(
        mesh_.MeshID(), prevMotion_.clip_, prevMotion_.timer_,
        mesh_.MeshID(), curMotion_.clip_, curMotion_.timer_, lerpTimer_ / constLerpTime,
        localBoneMatrices_.data());
    gsBindSkeleton(mesh_.MeshID());
    gsCalculateSkeleton(NULL, localBoneMatrices_.data(), boneMatrices_.data());
}

void AnimatedMesh::AddEvent(GSuint motion, GSfloat time, std::function<void()> callback)
{
    events_.push_back(new AnimationEvent(motion, time, callback));
}

int AnimatedMesh::MotionClip() const
{
    return curMotion_.clip_;
}

bool AnimatedMesh::IsEndMotion() const
{
    if (curMotion_.loop_)return false;
    return curMotion_.timer_ >= (MotionEndTime() - 1);
}

float AnimatedMesh::MotionTime() const
{
    return curMotion_.timer_;
}

void AnimatedMesh::MotionTime(float time)
{
    curMotion_.timer_ = time;
}

float AnimatedMesh::MotionEndTime() const
{
    return gsGetEndAnimationTime(mesh_.MeshID(), curMotion_.clip_);
}

float AnimatedMesh::MotionEndTime(GSuint motion) const
{
    return gsGetEndAnimationTime(mesh_.MeshID(), motion);
}

bool AnimatedMesh::IsMotion(int motion)
{
    return curMotion_.clip_ == motion;
}

GSuint AnimatedMesh::MeshID() const
{
    return mesh_.MeshID();
}

GSmatrix4 AnimatedMesh::boneMatrices(int boneNo) const
{
    return boneMatrices_[boneNo] * transform_;
}

int AnimatedMesh::MotionCount() const
{
    return gsGetNumAnimations(mesh_.MeshID());
}

void AnimatedMesh::UpdateLerpTimer(float deltaTime)
{
    //モーションの補間タイマーを進める
    lerpTimer_ = CLAMP(lerpTimer_ + deltaTime, 0, constLerpTime);
}

void AnimatedMesh::UpdateEvent(float deltaTime)
{
    float prevTimer = curMotion_.timer_;
    float nextTimer = UpdateMotionTimer(deltaTime, curMotion_);
    bool looped = nextTimer < prevTimer;
    for (const auto& event : events_)
    {
        if (event->motion_ != curMotion_.clip_)continue;

        if (looped)
        {
            if (prevTimer >= event->time_ && event->time_ > nextTimer) continue;
            event->callback_();
        }
        else
        {
            if (prevTimer >= event->time_ || event->time_ > nextTimer) continue;
            event->callback_();
        }
    }
}

float AnimatedMesh::UpdateMotionTimer(float deltaTime, Motion motion)
{
    return UpdateMotionTimer(deltaTime, motion.timer_, motion.speed_, motion.loop_, MotionEndTime(motion.clip_));
}

float AnimatedMesh::UpdateMotionTimer(float deltaTime, float timer, float motionSpeed, bool motionLoop, float motionEndTime)
{
    timer += deltaTime * motionSpeed;
    if (motionLoop) timer = std::fmod(timer, motionEndTime);
    else timer = std::min(timer, motionEndTime - 1.0f);

    return timer;
}

void AnimatedMesh::WeaponDraw(GSuint model, int boneNo)
{
    glPushMatrix();
        glMultMatrixf(boneMatrices(boneNo));
        gsDrawMesh(model);
    glPopMatrix();
}

void AnimatedMesh::Debug(const std::string& actorName)
{
    int motion = curMotion_.clip_;
    const int motionCount = MotionCount();
    ImGui::Begin((actorName +"Animation").c_str());
    ImGui::Value("AnimCount", motionCount);
    ImGui::Value("curAnim", curMotion_.clip_);
    ImGui::Value("cur", curMotion_.timer_);
    ImGui::Value("curLoop", curMotion_.loop_);
    ImGui::Value("curAnimSpeed", curMotion_.speed_);
    ImGui::Value("prevAnim", prevMotion_.clip_);
    ImGui::Value("prev", prevMotion_.timer_);
    ImGui::Value("prevLoop", prevMotion_.loop_);
    ImGui::Value("preAnimSpeed", prevMotion_.speed_);
    ImGui::Value("lerp", lerpTimer_);
    ImGui::InputInt("changeAnim",&motion);
    ImGui::End();
    motion = CLAMP(motion,0, motionCount - 1);
    if(curMotion_.clip_ != motion)ChangeMotion(motion,true);
}
