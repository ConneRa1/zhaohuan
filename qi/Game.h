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

class Game {
public:
	Game();
	~Game();
	void Run();
	friend class State;
	friend class FirstDiceState;
	friend class PlayerTurnState;
	friend class ChooseCardState;
private:
	RenderWindow window;	//����
	View view;
	bool isFullscreen = false;
	vector<Character> characterVector;	//��ɫ���������ڴ洢�������еĽ�ɫ
	vector<Enemy> enemyVector;	//�������������ڴ洢�������еĹ���
	vector<Card> heldCards;	//���еĿ�Ƭ
	vector<Card> discardPile;	//���ƶ��еĿ�Ƭ
	vector<Card> cardPile;	//�ƶ��еĿ�Ƭ
	vector<Object> dices;

	//display������
	vector<Card> card;
	vector<Object> sAbility;
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
	
	//����state��bool
	bool firstConfirm=false;


	//��Ϸ�����߼�
	void Initial();
	void Input();
	void Logic();
	void Draw();
	void toggleFullscreen();
	void LeftButtonDown(Vector2i mPoint);
	void RightButtonDown(Vector2i mPoint);
	//�Զ��������SMFL�Ļ�ͼ����
	//void myDraw(Texture& texture, float x, float y, float width = 0,float height=0);
};