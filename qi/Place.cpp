#include "Place.h"
Place::Place(PlaceType type, ConcreateCard name,int times, int num, int width, int height, Texture& texture) : Object(texture, width, height)
{
	this->name = name;
	this->type = type;
	this->times = times;
	this->num = num;
}
void Place::draw(RenderWindow& window) {
	Object::draw(window);
}
void Place::setPos(float x, float y) {
	Object::setPos(x, y);
}