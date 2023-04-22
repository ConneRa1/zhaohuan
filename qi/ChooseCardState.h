#pragma once
#include"base.h"
#include "State.h"
#include"Game.h"
class ChooseCardState :
    public State
{
public:
    ChooseCardState(Game* game);
    void Input();
    void Logic();
    void Draw();
    void ChangeCard();
private :
    bool ischanged = false;
};

