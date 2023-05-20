
#pragma once
#include "Object.h"
class Summoned:
    public Object
{
public:
    Summoned();
    Summoned( ConcreateCard name, int times, int num, int w, int h, Texture&);
    void draw(RenderWindow& window);
    void setPos(float x, float y);
    int times;  // 可用次数或所需次数
    int num;    //对应数值
    ConcreateCard name;
};