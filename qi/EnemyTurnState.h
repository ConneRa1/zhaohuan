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
    EnemyTurnState* clone() { EnemyTurnState* p = new EnemyTurnState(mGame); *p = *this; return p; }
private:
    bool isChangingRole = false;
    int times = 0;
    bool isChanged = false;
    Character* changedCharacter;
    Enemy* currentEnemy;
};

