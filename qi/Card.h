#pragma once
#include "Base.h"
#include "Object.h"
#include "Character.h"
#include"Cost.h"


class Card :public Object {
public:
	Card(Texture& texture, int width, int height, float x, float y,Cost cost ,CardType cardtype,bool=false);
	~Card();
	void draw(RenderWindow& window, float x, float y);
	void setScale(float x, float y);
	CardType cardtype;
	Cost cost;		//���ѵķ���
	//int cost;
	bool quickAction = false;		//��������ǲ��ǲ���ҪĿ��
protected:
	Role* target=NULL;
	bool isTriggered = false;
	
};

class CardVector {		//��װ��card����
public:
	CardVector() {};
	~CardVector() {};
	void draw(RenderWindow& window,float,float); //�������п���
	void push_back(Card* newCard);	//�Ż����п���
	void drawCard();	//���ƶ��г�һ���Ƶ����п�����
	void changeCard(Card* card);
	void changeCard(Card* card, float, float, float);
	void useCard(Card* card);		//ʹ�ÿ�Ƭ�����Ƶ����ƶ���
	Card* cardMouse(int x, int y);  //���ض�Ӧλ�õĿ�Ƭ��ָ��
	void setHeldCardsPosition(float, float,float);
	int getCardNum() { return heldCards.size(); }

	//ˢ��
	//�����ƶ��е���ȫ���Ż��Ŷ�
private:
	vector<Card*> heldCards;	//���еĿ�Ƭ
	vector<Card*> discardPile;	//���ƶ��еĿ�Ƭ
	vector<Card*> cardPile;	//�ƶ��еĿ�Ƭ
};




//class CardFactory {		//��Ƭ����
//public:
//	static Card* getCard(CardType num, Texture& texture, int width, int height, int x, int y)
//	{
//		
//
//	}
//};

