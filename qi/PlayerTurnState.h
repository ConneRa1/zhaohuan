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
private:
    int times = 0;
    bool isActed = false;
    bool isCardTriggered = false;
    bool isCardFinished = false;
    bool isAbilityTriggered = false;
    bool quickChange = false;
    bool isChangingRole = false;
    bool isChanged = false;
    bool isConsumingDice = false;
    bool flag = false;
    bool DiceConsumed = false;
    bool diceTriggered[8] = {0};
    int diceTriggeredNum = 0;
    vector<Object>placedDice;
    Role *target;
    Character* currentRole;
    Enemy* currentEnemy;
    Card* triggeredCard=NULL;
    Card *triggeredAbility;
};

