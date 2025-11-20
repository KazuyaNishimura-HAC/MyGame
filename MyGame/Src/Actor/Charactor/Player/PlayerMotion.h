#ifndef PLAYER_MOTION_H_
#define PLAYER_MOTION_H_
class PlayerMotion
{
public:
    enum Motion {
        Idle,
        Run,
        Hit,
        Die,
        Attack1,
        Attack2,
        Attack3,
        Attack4,
        ChargeATK,
        FullChargeATK,
        UltimateSkill,
        Guard,
        GuardHit1,
        GuardHit2,
        GuardHit3,
        GuardBreak,
        ParrySuccess,
        ParryATK,
        HeavyHit
    };
};

#endif
