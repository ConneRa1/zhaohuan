#include "Summoned.h"
Summoned::Summoned(ConcreateCard name, int times, int num, int width, int height, Texture& texture) : Object(texture, width, height)
{
	this->name = name;
	this->times = times;
	this->num = num;
}
void Summoned::draw(RenderWindow& window) {
	Object::draw(window);
}
void Summoned::setPos(float x, float y) {
	Object::setPos(x, y);
}