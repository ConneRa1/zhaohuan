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

private :
    int times = 0;
};

