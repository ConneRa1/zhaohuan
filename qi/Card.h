#pragma once
#include "Base.h"
#include "Object.h"
#include "Character.h"



class Card :public Object {
public:
	Card(Texture& texture, int width, int height, int x, int y);
	~Card();
	void triggered();
protected:
	int cost;
	int num;
	Character* owner;
	bool isTriggered;
	Texture tcard;	//Œ∆¿Ì
};



class CardFactory {		//ø®∆¨π§≥ß
public:
	static Card* getCard(CardType num, Texture& texture, int width, int height, int x, int y)
	{
		

	}
};