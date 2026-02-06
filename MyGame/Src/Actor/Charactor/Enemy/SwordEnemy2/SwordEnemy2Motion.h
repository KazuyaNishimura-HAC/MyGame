#ifndef SWORD_ENEMY2_MOTION_H_
#define SWORD_ENEMY2_MOTION_H_
class SwordEnemy2Motion
{
public:
    enum Motion
    {
        //共通モーションが6つあるためID6から
        Attack1 = 6,
        ChargeATK,
        Guard
    };
};

#endif
