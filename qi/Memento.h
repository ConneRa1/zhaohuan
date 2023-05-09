#pragma once
#include"State.h"
#include"Character.h"
#include"Card.h"
class Memento
{
public:
	//Memento();
	Memento(State* s, Game *game);
	vector<Character> characterVector;	//��ɫ���������ڴ洢�������еĽ�ɫ
	vector<Enemy> enemyVector;	//�������������ڴ洢�������еĹ���
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

