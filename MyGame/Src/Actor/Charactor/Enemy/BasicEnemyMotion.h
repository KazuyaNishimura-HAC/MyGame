#ifndef BASIC_ENEMY_MOTION_H_
#define BASIC_ENEMY_MOTION_H_
class BasicEnemyMotion
{
public:
    enum Motion
    {
        Idle,
        Run,
        Hit,
        Parried,
        //Stun,
        Die
    };
};

#endif
