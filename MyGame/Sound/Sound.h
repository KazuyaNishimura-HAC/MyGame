#ifndef SOUND_H_
#define SOUND_H_

class Sound
{
public:
    enum BGM
    {
        Stage1BGM,
        TitleBGM,
        ResultLoseBGM,
        ResultWinBGM
    };
    enum SE
    {
        //全SE取得用番号
        GetSEStart,
        //[Menu]
        MenuSelect,
        MenuConfirm,
        MenuPop,
        //[GameSE]
        CountDown,
        GetItem,
        FlipStart,
        FlipEnd,
        CarMove,
        ResultLose,
        ResultWin,
        AttackBullet,
        PlayerDamage,
        BodyHit,
        GameFinish,
        //[ItemSE]
        BoostItem,
        BullTankItem,
        MagicHandItemSpawn,
        MagicHandItemSeize,
        PlusFlipItem,
        ShieldItem,
        ItemRolling,
        ItemConfirmed,
        //[GimmickSE]
        Acceleration,
        //全SE取得用番号
        GetSEEnd
    };  

    enum SEGroup
    {
        Menu,
        GamePlay,
    };

    //SEグループを作って管理
    static int GroupBegin(SEGroup group)
    {
        static int groupBegin[2]
        {
            SE::MenuSelect,
            SE::CountDown,
        };
        return groupBegin[(int)group];
    }
    static int GroupEnd(SEGroup group)
    {
        static int groupEnd[2]
        {
            SE::MenuPop,
            SE::ResultWin,
        };
        return groupEnd[(int)group];
    }
};

#endif
