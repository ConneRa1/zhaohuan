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
    DrawCardState* clone() { DrawCardState* p = new DrawCardState(mGame); *p = *this; return p; }
private :
    int times = 0;
    Card* card1, *card2;
    Vector2f startPosition1;
    Vector2f endPosition1;
    Vector2f startPosition2;
    Vector2f endPosition2;
};

