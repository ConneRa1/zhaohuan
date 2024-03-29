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
#include "Ability.h"
#include "Cost.h"
class State;
#include"FirstDiceState.h"
#include"PlayerTurnState.h"
#include"ChooseCardState.h"
#include"EnemyTurnState.h"
#include"DrawCardState.h"
#include"GameEndState.h"
#include"TurnEndState.h"
#include"Memento.h"
#include"Place.h"
#include"Summoned.h"

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
	friend class TurnEndState;
	friend class Memento;
private:
	RenderWindow window;	//窗口
	View view;
	Cost diceNum;
	bool isFullscreen = false;
	vector<Character> characterVector;	//角色容器，用于存储场上所有的角色
	vector<Enemy> enemyVector;	//怪物容器，用于存储场上所有的怪物
	CardVector cards;
	vector<Object> dices;		//小骰子
	vector<vector<Place>> playerPlaceVector;		//玩家和敌人的场景卡容器	[0]是投掷骰子，[1]是换人,[2]是攻击，[4]是结束阶段
	vector<vector<Place>> enemyPlaceVector;

	vector<Summoned*> playerSummonedVector;		//玩家和敌人的召唤物容器
	vector<Summoned*> enemySummonedVector;


	//display测试用
	vector<Ability*> abilityVector;
	vector<Ability*> sAbility;		//用来存放显示、生效的技能

	vector<Object> rollDices;		//投骰子
	Object rollDicesbg[8];	
	vector<Object> chooseCards;
	Object abilityBanner[9];

	Texture texarr[500];

	Shader shader;
	vector<UI> ui;
	State* mState;

	bool gameOver, gameQuit;	//游戏运行阶段
	Texture tBackGround;	//纹理
	Object backGround;	//背景
	Object diceTriggerred[4];
	Object confirmButton;
	Object chooseDice;	//消耗骰子
	Object dicebg;
	Object chupai;
	Object Win;
	Object Lose;
	Object enemybanner;
	Object playerbanner;
	Object whenDice;
	Object whenEnd;
	Object changeTarget;
	Object changeConfirm;
	Object target;
	Object hurt;
	Object shui;
	Object lei;
	Object bing;
	Object huo;
	Object yan;
	Object feng;
	Object cao;
	Object heal1;
	Object heal2;
	
	//各个state的bool
	bool firstInitDice = true;
	bool firstConfirm=false;
	bool playerTurnOver = false;
	bool enemyTurnOver = false;
    int enemyAction = 2;
	bool isWin = false;
	bool initdice = true;
	bool isPlayerFirst = true;
	int enemyNum;

	Music bkMusic;
	vector<Memento> saves;

	//游戏基本逻辑
	void Initial();
	void Input();
	void Logic();
	void Draw();
	void toggleFullscreen();
	void LeftButtonDown(Vector2i mPoint);
	void RightButtonDown(Vector2i mPoint);
	void ChangeState(State* state);
	void showElement(Role it);
	void GetMemento();
	void LoadMemento(int);
	Enemy* CurrentEnemy();
	Character* CurrentCharacter();
	Character* NextCharacter();
	void placeVectorAutoPlace();
	
	void addPlayerPlace(Place);
	void addEnemyPlace(Place);
	void drawPlaceVector();
	void resetPlaceCardTimes();
	void drawAbilityBanner(Ability *);
	void summonedVectorAutoPlace();
	void drawSummonedVector();
	//自定的针对于SMFL的画图程序
	//void myDraw(Texture& texture, float x, float y, float width = 0,float height=0);
};