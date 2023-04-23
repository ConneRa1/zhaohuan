#pragma once
#include "State.h"
#include"base.h"
#include"Game.h"
class GameEndState :
    public State
{
public:
    GameEndState(Game* game);
    void Input();
    void Logic();
    void Draw();
    void ChangeCard();
};

