#pragma once
#include "Object.h"
class UI :
    public Object
{
public :
    UI();
    UI(Texture& texture, int width , int height , float x , float y,string name);
    string name;
    void update();
};

