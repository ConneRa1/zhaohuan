#pragma once
#include"Object.h"
#include"base.h"
class Buff:Object
{
public:
    Buff();
    Buff(int, Texture);
    void draw(RenderWindow& window, float x, float y);
private:
    int times;  //���ô���
    Sprite sprite;
};

