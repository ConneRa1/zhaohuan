#include "Card.h"
Card::~Card()
{
}
Card::Card(Texture& texture, int width, int height, float x, float y, int cost, bool quick) : Object(texture, width, height, x, y) {
	this->cost = cost;
	quickAction = quick;
}
void Card::draw(RenderWindow& window, float x, float y) {
	setScale(x, y);
	Object::draw(window);
}
void Card::setScale(float x, float y)
{
	sprite.setScale(x * (float)windowWidth * cardWidth / (float)sprite.getTexture()->getSize().x,
		y * (float)windowHeight * cardHeight / (float)sprite.getTexture()->getSize().y);
}


void CardVector::setHeldCardsPosition(float x,float y,float offset) {
	/*int times = 0;
	for (auto it = heldCards.begin(); it != heldCards.end(); it++) {
		(*it)->setPos(x + offset * times++, y);
	}*/
	heldCards[0]->setPos(x + offset *0, y);
	heldCards[1]->setPos(x + offset *1, y);
	heldCards[2]->setPos(x + offset *2, y);
	heldCards[3]->setPos(x + offset *3, y);
	heldCards[4]->setPos(x + offset *4, y);
}

void  CardVector::draw(RenderWindow& window,float x,float y) {
	int times = 0;
	for (auto it = heldCards.begin(); it != heldCards.end(); it++) {
		(*it)->draw(window,x,y);
	}

}

void  CardVector::push_back(Card* newCard) {
	cardPile.push_back(newCard);

}


void CardVector::drawCard() {
	//之后要写清楚，卡牌为空的情况
	/*srand((unsigned)time(0));
	heldCards.push_back(*(cardPile.begin() + rand()%(cardPile.size()-1)));
	cardPile.erase((cardPile.begin() + rand() % (cardPile.size() - 1)));*/
	heldCards.push_back(*(cardPile.begin()));
	cardPile.erase((cardPile.begin()));
}
void CardVector::changeCard(Card* card) {
	int index = 0;
	for (auto it = heldCards.begin(); it != heldCards.end(); it++) {
		if (*it == card)
		{
			heldCards.erase(it);
			break;
		}
		index++;
	}
	cout << "手牌id:" << index << "被换" << endl;
	srand((unsigned)time(NULL));
	int id = rand() % (cardPile.size());
	heldCards.insert(heldCards.begin() + index, *(cardPile.begin()+id));
	cardPile.erase(cardPile.begin()+id);
	cardPile.insert(cardPile.begin()+id, card);
}
void CardVector::changeCard(Card* card,float x,float y,float offset) {
	int index = 0;
	for (auto it = heldCards.begin(); it != heldCards.end(); it++) {
		if (*it == card)
		{
			heldCards.erase(it);
			break;
		}
		index++;
	}
	cout << "手牌id:" << index << "被换" << endl;
	heldCards.insert(heldCards.begin()+index, *(cardPile.end()-1));
	cardPile.pop_back();
	cardPile.insert(cardPile.begin(), card);
	heldCards[0]->setPos(x + offset * 0, y);
	heldCards[1]->setPos(x + offset * 1, y);
	heldCards[2]->setPos(x + offset * 2, y);
	heldCards[3]->setPos(x + offset * 3, y);
	heldCards[4]->setPos(x + offset * 4, y);
}


Card* CardVector::cardMouse(int x, int y) {
	for (auto it = heldCards.begin(); it != heldCards.end(); it++) {
		if ((*it)->isIn(x, y)) {
			return *it;
		}
	}
	return NULL;
}


void CardVector::useCard(Card* card) {
	for (auto it = heldCards.begin(); it != heldCards.end(); it++) {
		if ((*it) == card) {
			heldCards.erase(it);
			discardPile.push_back(card);
			return;
		}
	}
	return;
}