#pragma once
#include"Object.h"
#include"base.h"
class Buff:Object
{
public:
    Buff();
    Buff(int times,BuffType type,int num, int w,int h,Texture&);
    Buff(int times, BuffType type, int num, int w, int h,string name, Texture&);
    void draw(RenderWindow& window);
    void setPos(float x, float y);
    void setScale(float x, float y);
    float getScalex();
    float getScaley();
    Sprite getSprite() { return sprite; }
    int times;  //���ô���
    BuffType type;
    int num;    //��Ӧ��ֵ
    string name;
};

