#ifndef BOSS_MOTION_H_
#define BOSS_MOTION_H_
class BossMotion
{
public:
    enum Motion {
        Idle,
        Run,
        Hit,
        ParryHit,
        Die,
        Attack1,
        Attack2,
        Attack3,
        Attack4,
        Guard,
        GuardBreak,
        GuardHit,
        Jump,
        Walk
    };
};

#endif
