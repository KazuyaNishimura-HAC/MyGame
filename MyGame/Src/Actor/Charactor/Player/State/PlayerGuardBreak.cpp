#include "PlayerGuardBreak.h"
#include "../../../../World/IWorld.h"

PlayerGuardBreak::PlayerGuardBreak(Player* owner)
    :PlayerState::PlayerState(owner)
{
}

void PlayerGuardBreak::Update(float deltaTime)
{
    if (owner_->GetMesh()->IsEndMotion()) {
        owner_->ChangeMotion(PlayerMotion::Idle);
    }
}

void PlayerGuardBreak::Enter()
{
    owner_->ChangeMotion(PlayerMotion::HeavyHit,false);
    owner_->ResetGuardPoint();
    owner_->SetTimeScale(0.75f, 1.0f);
    owner_->GetPlayerCamera()->SetShakeValues(20.0f, 5.0f, 160.0f, 1.0f, 5.0f, { 0.1f,0.5f }, 0.0f);
}

void PlayerGuardBreak::Exit()
{
    
}

