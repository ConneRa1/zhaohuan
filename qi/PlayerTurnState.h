#pragma once
#include "State.h"
#include"base.h"
#include"Game.h"
class PlayerTurnState :
    public State
{
public:
    PlayerTurnState(Game* game);
    void Input() ;
    void Logic() ;
    void Draw() ;
    void LeftButtonDown(Vector2i mPoint);
    void RightButtonDown(Vector2i mPoint);

};

