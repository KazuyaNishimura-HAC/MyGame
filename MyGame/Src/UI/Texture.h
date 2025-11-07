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

        //Scene
        TitleText,
        LoadingText,
        ResultText


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
            {Name::TitleText,{180,67}},
            {Name::LoadingText,{257,69}},
            {Name::ResultText,{109,68}}

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
