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
	Cost cost;		//花费的费用
	//int cost;
	bool quickAction = false;		//看这个牌是不是不需要目标
	ConcreateCard name;
protected:
	bool isTriggered = false;
};

class CardVector {		//封装的card容器
public:
	CardVector() {};
	~CardVector() {};
	void draw(RenderWindow& window,float,float); //画出手中卡牌
	void push_back(Card* newCard);	//放回手中卡牌
	void drawCard();	//从牌堆中抽一张牌到持有卡牌中
	void changeCard(Card* card);
	void changeCard(Card* card, float, float, float);
	void useCard(Card* card);		//使用卡片，弃牌到弃牌堆中
	void setHeldCardsPositionY();
	Card* cardMouse(int x, int y);  //返回对应位置的卡片的指针
	void setHeldCardsPosition(float, float,float);
	int getCardNum() { return heldCards.size(); }
	Card* getCard(int i) { return (*(cardPile.begin() + i)); }
	void autoPlace() { setHeldCardsPosition(0.5 - (getCardNum()) * cardWidth / 4, heldCardY, cardWidth * 0.52); };
	//刷牌
	//把弃牌堆中的牌全部放回排队
private:
	vector<Card*> heldCards;	//持有的卡片
	vector<Card*> discardPile;	//弃牌堆中的卡片
	vector<Card*> cardPile;	//牌堆中的卡片
};




class CardFactory {		//卡片工厂
public:
	static Card* CreateCard( Texture& texture,int cost,CardType type,ConcreateCard name ,bool quick)
	{
		return new Card(texture, windowWidth * chooseCardWidth, windowHeight * chooseCardHeight, chooseCardX, chooseCardY, Cost(1, pair<ElementType, int>(ElementType::cai, cost)),type ,name, quick);
	}
};

