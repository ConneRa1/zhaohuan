#include "Card.h"
Card::~Card()
{
}
Card::Card(Texture& texture, int width, int height, float x, float y,Cost c, CardType cardtype,ConcreateCard name, bool quick) : Object(texture, width, height, x, y) {
	quickAction = quick;
	cost = c;
	this->cost = cost;
	this->name = name;
	this->cardtype = cardtype;
}
Card::Card(Texture& texture, int width, int height, float x, float y, Cost c) : Object(texture, width, height, x, y) {
	this->cost = c;
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
	int times = 0;
	for (auto it = heldCards.begin(); it != heldCards.end(); it++) {
		(*it)->setPos(x + offset * times++, y);
	}
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
	//֮��Ҫд���������Ϊ�յ����
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
	cout << "����id:" << index << "����" << endl;
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
	cout << "����id:" << index << "����" << endl;
	heldCards.insert(heldCards.begin()+index, *(cardPile.end()-1));
	cardPile.pop_back();
	cardPile.insert(cardPile.begin(), card);

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


