#include "BossJumpAttack.h"
#include "../../../../../GameSystem/Vibration/VibrationManager.h"
BossJumpAttack::BossJumpAttack(Boss* owner)
    :BossState::BossState(owner)
{
    //攻撃処理
    owner_->GetMesh()->AddEvent(BossMotion::Jump, 60, [=] {
        Attack();
        Effect::SetEffectParam({ Effect::GroundDust, { 0,0,0 }, { 0,0,0 }, { 2,2,2 }, { 1,1,1,1 }, 1 }, owner_->Transform());
        });
}

void BossJumpAttack::Update(float deltaTime)
{
    
    if (waitTimer_ != 0.0f && owner_->GetMesh()->MotionTime() >= 30.0f) {
        owner_->GetMesh()->MotionTime(30.0f);
        if (!isWait_)isWait_ = true;
    }
    if (isWait_) {
        waitTimer_ -= deltaTime / 60.0f;
        if (waitTimer_ < 0.0f) {
            waitTimer_ = 0.0f;
            isWait_ = false;
        }
    }
    else {
        int updown = 1;
        if (waitTimer_ == 0.0f) updown = -1;
        else updown = 1;
        owner_->UpDown(0.5f * updown);

        if (updown == -1) {
            GSvector3 playerPos = owner_->GetPlayer()->Transform().position();
            GSvector3 movePos = playerPos;
            //y座標は位置を変えない
            movePos.y = owner_->Transform().position().y;
            owner_->Transform().position(movePos);
        }
        
    }

    if (owner_->GetMesh()->IsEndMotion() && owner_->Transform().position().y <= 0.0f) {
        owner_->ChangeState(BossState::Idle);
    }
}

void BossJumpAttack::Enter()
{
    owner_->SetAttack(true);
    owner_->LookAtPlayer();
    owner_->ChangeMotion(BossMotion::Jump, false);
    waitTimer_ = waitduration;
}

void BossJumpAttack::Exit()
{
    owner_->SetAttack(false);
    GSvector3 currentPos = owner_->Transform().position();
    currentPos.y = 0;
    owner_->Transform().position(currentPos);
}

void BossJumpAttack::Attack()
{
    //Effect::SetEffectParam(currentEffect_, owner_->Transform());
    owner_->NormalAttack();
}
