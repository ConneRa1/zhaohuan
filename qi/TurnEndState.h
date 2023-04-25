#pragma once
#include"base.h"
#include "State.h"
#include"Game.h"
class TurnEndState :
    public State
{
public:
    TurnEndState(Game* game);
    void Input();
    void Logic();
    void Draw();
    int times = 0;
};

