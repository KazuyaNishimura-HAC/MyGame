#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <gslib.h>

class Texture
{
public:
    enum Name
    {
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

        //Game
        NumberText,
        BossMenuSliderBG,
        BossSliderFill,
        HPGaugeBG,
        HPGaugeFill,
        SkillGaugeBG,
        SkillGaugeFill,
        UltimateIconBG,
        UltimateIconFill,
        HitText,
        
        //Title
        TitleLogo,
        PressButtonText,
        TitleBGImage,
        //Loading
        LoadingText,
        //Result
        ResultText,
        RankText,
        RankS,
        RankA,
        RankB,
        RankC,
        MaxComboText,
        ParryCountText,
        TotalDamageText,
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
            {Name::NumberText,{2240,256}},
            {Name::BossMenuSliderBG,{256,42}},
            {Name::BossSliderFill,{256,42}},
            {Name::HPGaugeBG,{256,42}},
            {Name::HPGaugeFill,{256,42}},
            {Name::SkillGaugeBG,{183,20}},
            {Name::SkillGaugeFill,{183,20}},
            {Name::UltimateIconBG,{256,256}},
            {Name::UltimateIconFill,{256,256}},
            {Name::HitText,{643,397} },
            {Name::TitleLogo,{2048,512} },
            {Name::PressButtonText,{2520/*2862*/,397} },
            {Name::TitleBGImage,{1920,1080} },
            {Name::LoadingText,{1231,397} },
            {Name::ResultText,{129,397}},
            {Name::RankText,{816,397}},
            {Name::RankS,{1024,1024}},
            {Name::RankA,{1024,1024}},
            {Name::RankB,{1024,1024}},
            {Name::RankC,{1024,1024}},
            {Name::MaxComboText,{1628,397}},
            {Name::ParryCountText,{1940,397}},
            {Name::TotalDamageText,{2192,397}}

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
