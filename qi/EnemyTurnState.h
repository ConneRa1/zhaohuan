#pragma once
#include"base.h"
#include "State.h"
#include"Game.h"
class EnemyTurnState :
    public State
{
public:
    EnemyTurnState(Game* game);
    void Input();
    void Logic();
    void Draw();
    void ChangeCard();
private:
    bool isChangingRole = false;
    int times = 0;
    Role* target;
    Character* changedCharacter;

};

