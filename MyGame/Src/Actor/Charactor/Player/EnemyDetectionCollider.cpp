#include "EnemyDetectionCollider.h"
#include "Player.h"

EnemyDetectionCollider::EnemyDetectionCollider(Player* player, float radius, const GSvector3& pos, const GSvector3& offset)
    :player_{ player }
{
    tag_ = ActorTag::Collider;
    //攻撃主の名前を登録
    name_ = ActorName::DetectionCollider;
    collider_ = BoundingSphere(radius, pos);
    colliderOffset_ = offset;
    collider_.Trigger(true);
    collider_.SetEnable(true);
}

EnemyDetectionCollider::~EnemyDetectionCollider()
{

}

void EnemyDetectionCollider::Update(float deltaTime)
{
    //前フレーム時の要素をクリア
    reactActorList_.clear();
    collider_.Position(transform_.position() + colliderOffset_);
}

void EnemyDetectionCollider::LateUpdate(float deltTime)
{
    GSvector3 playerPos = player_->Transform().position();
    if (!reactActorList_.empty()) {
        player_->SetEnemyNearby(true);
        float minDist = GSvector3::distance(playerPos, reactActorList_[0]->Transform().position());
        for (const auto& reactActor : reactActorList_) {
            float dist = GSvector3::distance(playerPos, reactActor->Transform().position());
            if (dist <= minDist) {
                minDist = dist;
                player_->SetNearbyEnemyPos(reactActor->Transform().position());
            }
        }
    }
    else {
        player_->SetEnemyNearby(false);
        player_->SetNearbyEnemyPos({ 0,0,0 });
    }
}

void EnemyDetectionCollider::Draw() const
{
    //デバック用
    collider_.Draw();
}
void EnemyDetectionCollider::React(Actor& other)
{
    if (other.GetTag() != ActorTag::Enemy) return;
    reactActorList_.push_back(&other);
}
