#pragma once

#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include "Base.h"
#include "Object.h"
#include "Buff.h"
#include "Card.h"
#include "Character.h"
#include "Role.h"
#include "Enemy.h"
#include "Object.h"
#include"UI.h"
class State;
#include"FirstDiceState.h"
#include"PlayerTurnState.h"
#include"ChooseCardState.h"
#include"EnemyTurnState.h"
#include"ChangeRoleState.h"
#include"DrawCardState.h"
#include"GameEndState.h"
class Game {
public:
	Game();
	~Game();
	void Run();
	friend class State;
	friend class FirstDiceState;
	friend class PlayerTurnState;
	friend class ChooseCardState;
	friend class EnemyTurnState;
	friend class ChangeRoleState;
	friend class DrawCardState;
	friend class GameEndState;
private:
	RenderWindow window;	//����
	View view;
	int diceNum = 8;
	bool isFullscreen = false;
	vector<Character> characterVector;	//��ɫ���������ڴ洢�������еĽ�ɫ
	vector<Enemy> enemyVector;	//�������������ڴ洢�������еĹ���
	CardVector cards;
	vector<Object> dices;

	//display������
	vector<Card> sAbility;
	vector<Object> rollDices;
	vector<Object> chooseCards;
	Texture texarr[500];
	Shader shader;
	vector<UI> ui;
	State* mState;

	bool gameOver, gameQuit;	//��Ϸ���н׶�
	Texture tBackGround;	//����
	Object backGround;	//����
	Object confirmButton;
	Object chooseDice;
	Object dicebg;
	Object chupai;
	Object Win;
	Object Lose;
	Object enemybanner;
	Object playerbanner;
	Object whenDice;
	Object whenEnd;

	
	//����state��bool
	bool firstConfirm=false;
	bool playerTurnOver = false;
	bool enemyTurnOver = false;
    int enemyAction = 2;
	bool isWin = false;
	bool initdice = true;

	Music bkMusic;


	//��Ϸ�����߼�
	void Initial();
	void Input();
	void Logic();
	void Draw();
	void toggleFullscreen();
	void LeftButtonDown(Vector2i mPoint);
	void RightButtonDown(Vector2i mPoint);
	void DrawCard();
	void ChangeState(State* state);
	//�Զ��������SMFL�Ļ�ͼ����
	//void myDraw(Texture& texture, float x, float y, float width = 0,float height=0);
};