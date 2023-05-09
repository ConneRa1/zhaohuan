#pragma once
#include "State.h"
#include"base.h"
#include"Game.h"
#include "PlayerTurnState.h"
class FirstDiceState :public State
{
public :
    FirstDiceState(Game* game);
    void Input() override;
    void Logic()override;
    void Draw()override;
    FirstDiceState* clone() { FirstDiceState* p = new FirstDiceState(mGame); *p = *this; return p; }
private :
    int times = 0;
};

