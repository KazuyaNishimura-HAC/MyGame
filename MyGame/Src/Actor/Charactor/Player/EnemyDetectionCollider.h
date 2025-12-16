#ifndef ENEMY_DETECTION_COLLIDER_H_
#define ENEMY_DETECTION_COLLIDER_H_
#include "../../Actor.h"

class Player;

class EnemyDetectionCollider : public Actor
{
public:
    EnemyDetectionCollider(Player* player, float radius = 1.0f, const GSvector3& pos = { 0,0,0 }, const GSvector3& offset = { 0,0,0 });
    ~EnemyDetectionCollider();
    void Update(float deltTime)override;
    void LateUpdate(float deltTime)override;
    void Draw()const override;
    void React(Actor& other)override;
private:
    Player* player_{ nullptr };
    std::vector<Actor*> reactActorList_;
};

#endif
