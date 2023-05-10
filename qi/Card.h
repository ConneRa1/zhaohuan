#pragma once
#include "Base.h"
#include "Object.h"
#include "Character.h"
#include"Cost.h"


class Card :public Object {
public:
	Card(Texture& texture, int width, int height, float x, float y,Cost cost ,CardType cardtype,ConcreateCard c,bool=false);
	Card(Texture& texture, int width, int height, float x, float y, Cost c);
	Card() {};
	~Card();
	void draw(RenderWindow& window, float x, float y);
	void setScale(float x, float y);
	void setPosition(Vector2f v) { sprite.setPosition(v); }
	Card* clone() { Card* c = new Card(); *c = *this; return c; }
	CardType cardtype;
	Cost cost;		//���ѵķ���
	//int cost;
	bool quickAction = false;		//��������ǲ��ǲ���ҪĿ��
	ConcreateCard name;
protected:
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
	void setHeldCardsPositionY();
	Card* cardMouse(int x, int y);  //���ض�Ӧλ�õĿ�Ƭ��ָ��
	void setHeldCardsPosition(float, float,float);
	int getCardNum() { return heldCards.size(); }
	Card* getCard(int i) { return (*(cardPile.begin() + i)); }
	void autoPlace() { setHeldCardsPosition(0.5 - (getCardNum()) * cardWidth / 4, heldCardY, cardWidth * 0.52); };
	//ˢ��
	//�����ƶ��е���ȫ���Ż��Ŷ�
private:
	vector<Card*> heldCards;	//���еĿ�Ƭ
	vector<Card*> discardPile;	//���ƶ��еĿ�Ƭ
	vector<Card*> cardPile;	//�ƶ��еĿ�Ƭ
};




class CardFactory {		//��Ƭ����
public:
	static Card* CreateCard( Texture& texture,int cost,CardType type,ConcreateCard name ,bool quick)
	{
		return new Card(texture, windowWidth * chooseCardWidth, windowHeight * chooseCardHeight, chooseCardX, chooseCardY, Cost(1, pair<ElementType, int>(ElementType::cai, cost)),type ,name, quick);
	}
};

