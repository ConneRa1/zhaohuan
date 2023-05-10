#include "Equipment.h"
Equipment::Equipment(int times, int num, int width, int height, Texture& texture) : Object(texture, width, height)
{
	this->times = times;
	this->num = num;
}
void Equipment::draw(RenderWindow& window) {
	Object::draw(window);
}
void Equipment::setPos(float x, float y) {
	Object::setPos(x, y);
}