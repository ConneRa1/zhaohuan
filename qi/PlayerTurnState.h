#pragma once
#include "State.h"
#include"base.h"
#include"Game.h"
#include "Cost.h"
class PlayerTurnState :
    public State
{
public:
    PlayerTurnState(Game* game);
private:
    void Input() ;
    void Logic() ;
    void Draw() ;
    void LeftButtonDown(Vector2i mPoint);
    void RightButtonDown(Vector2i mPoint);
    void doReact(ReactType r, bool toEnemy);
    void CancelConsumingDice(Vector2i mPoint);
    bool CheckChupai(Vector2i mPoint);
    PlayerTurnState* clone() {PlayerTurnState* p = new PlayerTurnState(mGame); *p = *this; return p;}
    void HandleCard(Card* c);
    int times = 0;
    int selectedDiceNum = 0;    //专门记录选择的骰子数的
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
    bool hurtOver = false;
    bool reactHurtOver = false;
    //Cost diceTriggeredNum= Cost(1, pair<ElementType, int>(ElementType::cai, 0));
    Cost diceTriggeredNum/*= Cost(1, pair<ElementType, int>(ElementType::cai, 0))*/;
    vector<Object>placedDice;
    
    Character* currentRole;
    Enemy* currentEnemy;
    Card* triggeredCard=NULL;
    Ability*triggeredAbility;
};

