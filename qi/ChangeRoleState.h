#pragma once
#include"base.h"
#include "State.h"
#include"Game.h"
class ChangeRoleState :
    public State
{
public:
    ChangeRoleState(Game* game);
    void Input();
    void Logic();
    void Draw();
    void ChangeCard();
private:
    bool ischanged = false;
};

