#pragma once
#include "Object.h"
class Place :
    public Object
{
public:
    Place();
    Place(PlaceType type, ConcreateCard name, int times,  int num, int w, int h, Texture&);
    void draw(RenderWindow& window);
    void setPos(float x, float y);
    int times;  // 可用次数或所需次数
    PlaceType type;
    int num;    //对应数值
    ConcreateCard name;
};

