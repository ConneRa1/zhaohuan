#include "Ability.h"

Ability::Ability(ElementType e, int d, Texture& texture, int width, int height, float x, float y, Cost cost):Card(texture,width, height,x,y,cost,CardType::ability) {
	element = e;
	damage = d;
}