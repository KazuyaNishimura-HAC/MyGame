#ifndef VALUE_TEXT_H_
#define VALUE_TEXT_H_

#include "GUI.h"
#include "Texture.h"

class ValueText :public GUI
{
public:
    /// <summary>
    /// 
    /// </summary>
    /// <param name="align">左揃え0, 右揃え1</param>
    ValueText(GSvector2 position,GSvector2 size = { 1,1 }, GScolor color = { 1, 1, 1, 1 }, int value = 0, float align = 1);
    virtual void Update(float deltaTime) override;
    virtual void Draw()const override;
    void UpdateValue(int value, float align = 1);
    void NumberFill(int num = 0);
    virtual GSuint Texture()const override;
protected:
    void DrawNumber(int num, float digit)const;
    int value_, digit_;
    int  fill_{ 0 };
    Texture::Data numbers_{ Texture::NumberText };
    float align_;
};

#endif
