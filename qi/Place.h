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
    int times;  // ���ô������������
    PlaceType type;
    int num;    //��Ӧ��ֵ
    ConcreateCard name;
};

