#ifndef SOUND_H_
#define SOUND_H_

class Sound
{
public:
    enum BGM
    {
        Battle,
        BossBattle,
        Title,
        Result,
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
        Attack,
        Footstep,
        Guard,
        Hit,
        Parry,
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
            SE::Attack,
        };
        return groupBegin[(int)group];
    }
    static int GroupEnd(SEGroup group)
    {
        static int groupEnd[2]
        {
            SE::MenuPop,
            SE::Parry,
        };
        return groupEnd[(int)group];
    }
};

#endif
