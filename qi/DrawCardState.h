#pragma once
#include"base.h"
#include "State.h"
#include"Game.h"
class DrawCardState :
    public State
{
public:
    DrawCardState(Game* game);
    void Input();
    void Logic();
    void Draw();
    void ChangeCard();
private :
    int times = 0;
};

