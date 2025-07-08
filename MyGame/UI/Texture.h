#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <gslib.h>

class Texture
{
public:
    enum Name
    {
        ////SkyBox
        //SkyBox,

        ////Octree
        //Stage1,
        //Stage1Collider,

        //Gamepad
        GamepadA,
        GamepadB,
        GamepadX,
        GamepadY,
        GamepadArrowUp,
        GamepadArrowDown,
        GamepadArrowLeft,
        GamepadArrowRight,
        GamepadLB,
        GamepadRB,
        GamepadLT,
        GamepadRT,
        GamepadLeftStick,
        GamepadRightStick,
        GamepadStickBG,
        ButtonHold,

        //Sound
        SoundAll,
        SoundBGM,
        SoundSE,
        MenuSliderBackGround,
        MenuSliderFill,

        //Scene
        TitleLogo,
        BackTitle,
        PushToA,

        //GamePlayUI
        BulletGauge,
        BulletGaugeFrame,
        MagIcon,
        MagGauge1,
        MagGauge2,
        UIBackGround,
        ItemFrame,
        Win,
        Lose,
        Count3,
        Count2,
        Count1,
        CountGO,
        BoostItem,
        PlusFlipItem,
        ShieldItem,
        MagicHandItem,
        BullTankItem,
        BullTankFace,
        BullTankEyes,
        BullTankLine,
        TextNumber,
        TextLine,
        TextPeriod,
        TextColon,
        TextTimeLogo,
        PushToStartLogo,
        PlayerFront,
        PlayerBack,
        Sight,
        Loading,
        LoadingCarR,
        LoadingCarB,
        //SelectScene
        BackB,
        StartA,
        GamePadIcon,
        TwoGamePadIcon,
        ConnectedGamepad,
        SelectFrame1,
        SelectFrame2,
        SelectFrame3,
        SelectActiveShadow,
        SelectLine,
        EasyTexture,
        NormalTexture,
        DifficultTexture,
        Stage1Texture,
        Stage2Texture,
        Stage3Texture,
        CPUTexture,
        LocalTexture,
        GameBG,
        Stage1Image,
        Stage2Image,
        Stage3Image,
        CPUEasy,
        CPUNormal,
        CPUDifficult

    };
    static GSvector2 GetSize(int id)
    {
        struct TextureData
        {
            Name name_;
            GSvector2 size_;
            TextureData(Name name, GSvector2 size) :name_{ name }, size_{ size } {}
        };
        static const TextureData data[]
        {
            //[Gamepad]
            {Name::GamepadA,{101,101}},
            {Name::GamepadB,{101,101}},
            {Name::GamepadX,{101,101}},
            {Name::GamepadY,{101,101}},
            {Name::GamepadArrowUp,{101,101}},
            {Name::GamepadArrowDown,{101,101}},
            {Name::GamepadArrowLeft,{101,101}},
            {Name::GamepadArrowRight,{101,101}},
            {Name::GamepadLB,{296,127}},
            {Name::GamepadRB,{296,127}},
            {Name::GamepadLT,{159,187}},
            {Name::GamepadRT,{159,187}},
            {Name::GamepadLeftStick,{168,168}},
            {Name::GamepadRightStick,{168,168}},
            {Name::GamepadStickBG,{201,201}},
            {Name::ButtonHold,{75,30}},


            {Name::SoundAll,{90,50}},
            {Name::SoundBGM,{90,50}},
            {Name::SoundSE,{126,50}},
            {Name::MenuSliderBackGround,{256,42}},
            {Name::MenuSliderFill,{256,42}},

            {Name::TitleLogo,{1500,1500}},
            {Name::BackTitle,{320,50}},
            {Name::PushToA,{642,167}},

            {Name::BulletGauge,{716,683}},
            {Name::BulletGaugeFrame,{1236,2252}},
            {Name::MagIcon,{400,50}},
            {Name::MagGauge1,{400,50}},
            {Name::MagGauge2,{400,50}},
            {Name::UIBackGround,{1920,1080}},
            {Name::ItemFrame,{342,342}},
            {Name::Win,{1024,1024}},
            {Name::Lose,{1024,1024}},
            {Name::Count3,{1024,1024}},
            {Name::Count2,{1024,1024}},
            {Name::Count1,{1024,1024}},
            {Name::CountGO,{1024,1024}},
            {Name::BoostItem,{342,342}},
            {Name::PlusFlipItem,{342,342}},
            {Name::ShieldItem,{342,342}},
            {Name::MagicHandItem,{342,342}},
            {Name::BullTankItem, {342, 342}},
            {Name::BullTankFace, {1024, 1024}},
            {Name::BullTankEyes, {1024, 1024}},
            {Name::BullTankLine, {1024, 1024}},
            {Name::TextNumber,{420,72}},
            {Name::TextLine,{43,65}},
            {Name::TextPeriod,{24,20}},
            {Name::TextColon,{18,50}},
            {Name::TextTimeLogo,{164,74}},
            {Name::PushToStartLogo,{1024,367}},
            {Name::PlayerFront,{1172,370}},
            {Name::PlayerBack,{1172,370}},
            {Name::Sight,{218,218}},
            {Name::Loading, {500, 500}},
            {Name::LoadingCarR, {1239, 338}},
            {Name::LoadingCarB, {1239, 338}},

            {Name::BackB,{499,164}},
            {Name::StartA,{532,232}},
            {Name::GamePadIcon,{361,219}},
            {Name::TwoGamePadIcon,{800,242}},
            {Name::ConnectedGamepad,{2413,241}},
            {Name::SelectFrame1,{775,459}},
            {Name::SelectFrame2,{544,572}},
            {Name::SelectFrame3,{774,979}},
            {Name::SelectActiveShadow,{351,93}},
            {Name::SelectLine,{7,1053}},
            {Name::EasyTexture,{653,213}},
            {Name::NormalTexture,{475,204}},
            {Name::DifficultTexture,{818,193}},
            {Name::Stage1Texture,{654,492}},
            {Name::Stage2Texture,{654,492}},
            {Name::Stage3Texture,{654,492}},
            {Name::CPUTexture,{308,132}},
            {Name::LocalTexture,{788,198}},
            {Name::GameBG,{1920,1200}},
            {Name::Stage1Image,{592,432}},
            {Name::Stage2Image,{592,432}},
            {Name::Stage3Image,{592,432}},
            {Name::CPUEasy,{1204,900}},
            {Name::CPUNormal,{1204,900}},
            {Name::CPUDifficult,{1204,900}}

        };
        return data[id].size_;
    }
    struct Data
    {
        GSuint name_;
        GSvector2 size_;
        GSvector2 centerAlign_{ 0.5f,0.5f };
        Data(GSuint name)
            :name_{ name }
        {
            size_ = Texture::GetSize(name);
        };
        Data(GSuint name, GSvector2 align)
            :name_{ name }, centerAlign_{ align }
        {
            size_ = Texture::GetSize(name);
        }
    };
};

#endif
