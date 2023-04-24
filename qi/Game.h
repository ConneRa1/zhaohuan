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
	RenderWindow window;	//窗口
	View view;
	int diceNum = 8;
	bool isFullscreen = false;
	vector<Character> characterVector;	//角色容器，用于存储场上所有的角色
	vector<Enemy> enemyVector;	//怪物容器，用于存储场上所有的怪物
	CardVector cards;
	vector<Object> dices;

	//display测试用
	vector<Card> sAbility;
	vector<Object> rollDices;
	vector<Object> chooseCards;
	Texture texarr[500];
	Shader shader;
	vector<UI> ui;
	State* mState;

	bool gameOver, gameQuit;	//游戏运行阶段
	Texture tBackGround;	//纹理
	Object backGround;	//背景
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

	
	//各个state的bool
	bool firstConfirm=false;
	bool playerTurnOver = false;
	bool enemyTurnOver = false;
    int enemyAction = 2;
	bool isWin = false;
	bool initdice = true;

	Music bkMusic;


	//游戏基本逻辑
	void Initial();
	void Input();
	void Logic();
	void Draw();
	void toggleFullscreen();
	void LeftButtonDown(Vector2i mPoint);
	void RightButtonDown(Vector2i mPoint);
	void DrawCard();
	void ChangeState(State* state);
	//自定的针对于SMFL的画图程序
	//void myDraw(Texture& texture, float x, float y, float width = 0,float height=0);
};