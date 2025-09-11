#ifndef ULTIMATE_ANIM__EVENT_H_
#define ULTIMATE_ANIM__EVENT_H_
#include "Event.h"

class GUI;
class Player;

class UltimateAnimEvent : public Event
{
public:
    UltimateAnimEvent(IWorld* world,int invokeType, const GSvector3& position = { 0,0,0 }, GSvector2 size = { 1,1 });
    void Update(float deltaTime) override;
    void Draw()const override;
private:
    void BeginEvent()override;
    void EndEvent()override;

    Player* player_{ nullptr };

    float distanceBack = 0.0f;  // �v���C���[�̔w��ɉ����鋗��
    float distanceSide = 0.0f; //�v���C���[�̍��E�ɂ����鋗��
    float height = 0.0f;  // �v���C���[�̏�����̍���
    float intensity = 0.35f;
};

#endif