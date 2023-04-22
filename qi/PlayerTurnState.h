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
    bool isActed = false;
    bool isCardTriggered = false;
    bool isCardFinished = false;
    bool isAbilityTriggered = false;
    bool quickChange = false;
    bool isChangingRole = false;
    Role *target;
    Card* triggeredCard=NULL;
    Card *triggeredAbility;
};

