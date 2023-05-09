#pragma once
#include"State.h"
#include"Character.h"
#include"Card.h"
class Memento
{
public:
	//Memento();
	Memento(State* s, Game *game);
	vector<Character> characterVector;	//角色容器，用于存储场上所有的角色
	vector<Enemy> enemyVector;	//怪物容器，用于存储场上所有的怪物
	CardVector cards;
	Cost diceNum;
	bool firstInitDice = true;
	bool firstConfirm = false;
	bool playerTurnOver = false;
	bool enemyTurnOver = false;
	int enemyAction = 2;
	bool isWin = false;
	bool initdice = true;
	bool isPlayerFirst = true; 
	State *save;
};

