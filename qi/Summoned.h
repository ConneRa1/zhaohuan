
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
    int times;  // ���ô������������
    int num;    //��Ӧ��ֵ
    ConcreateCard name;
};