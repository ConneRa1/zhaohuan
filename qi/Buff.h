#pragma once
#include"Object.h"
#include"base.h"
class Buff:Object
{
public:
    Buff();
    Buff(int times,BuffType type,int num, int w,int h,Texture&);
    void draw(RenderWindow& window);
    void setPos(float x, float y);
    int times;  //���ô���
    BuffType type;
    int num;    //��Ӧ��ֵ
private:
    Sprite sprite;
};

