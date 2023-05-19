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
	RenderWindow window;	//����
	View view;
	Cost diceNum;
	bool isFullscreen = false;
	vector<Character> characterVector;	//��ɫ���������ڴ洢�������еĽ�ɫ
	vector<Enemy> enemyVector;	//�������������ڴ洢�������еĹ���
	CardVector cards;
	vector<Object> dices;		//С����
	vector<vector<Place>> playerPlaceVector;		//��Һ͵��˵ĳ���������	[0]��Ͷ�����ӣ�[1]�ǻ���,[2]�ǹ�����[4]�ǽ����׶�
	vector<vector<Place>> enemyPlaceVector;


	//display������
	vector<Ability*> abilityVector;
	vector<Ability*> sAbility;		//���������ʾ����Ч�ļ���

	vector<Object> rollDices;		//Ͷ����
	Object rollDicesbg[8];	
	vector<Object> chooseCards;
	Object abilityBanner[9];

	Texture texarr[500];

	Shader shader;
	vector<UI> ui;
	State* mState;

	bool gameOver, gameQuit;	//��Ϸ���н׶�
	Texture tBackGround;	//����
	Object backGround;	//����
	Object diceTriggerred[4];
	Object confirmButton;
	Object chooseDice;	//��������
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
	
	//����state��bool
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

	//��Ϸ�����߼�
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
	void placeVectorAutoPlace();
	void addPlayerPlace(Place);
	void addEnemyPlace(Place);
	void drawPlaceVector();
	void resetPlaceCardTimes();
	void drawAbilityBanner(Ability *);
	//�Զ��������SMFL�Ļ�ͼ����
	//void myDraw(Texture& texture, float x, float y, float width = 0,float height=0);
};