#ifndef SWORD_ENEMY1_MOTION_H_
#define SWORD_ENEMY1_MOTION_H_
class SwordEnemy1Motion
{
public:
    enum Motion
    {
        //共通モーションが5つあるためID5から
        Attack1 = 5,
        ParryHit,
        Stan
    };
};

#endif
