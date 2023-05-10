#pragma once
#include"Object.h"
#include"base.h"
class Equipment:Object
{
protected:
	Equipment();
    Equipment(int times, int num, int w, int h, Texture&);
    void draw(RenderWindow& window);
    void setPos(float x, float y);
    int times;  //一回合可用次数
    int num;    //对应数值
};

