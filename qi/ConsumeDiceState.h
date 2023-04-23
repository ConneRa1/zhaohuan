#pragma once
#include"base.h"
#include "State.h"
#include"Game.h"
class ConsumeDiceState :
    public State
{
public:
    ConsumeDiceState(Game* game);
    void Input();
    void Logic();
    void Draw();
    void LeftButtonDown(Vector2i mPoint);
private:
    bool dicePlaced = false;
    int times = 0;
    vector<Object> placedDice;
};

