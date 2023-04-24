#pragma once
#include "Card.h"
class Ability :
    public Card{
public:
    Ability(ElementType e,int d, Texture& texture, int width, int height, float x, float y, Cost cost);
private:
    ElementType element;
    int damage;
};






