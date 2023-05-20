#include "Buff.h"
Buff::Buff(int times, BuffType type, int num,int width,int height, Texture &texture) : Object(texture, width, height)
{
	this->times = times;
	this->type = type;
	this->num = num;
}
Buff::Buff(int times, BuffType type, int num,int width,int height,string name, Texture &texture) : Object(texture, width, height)
{
	this->name = name;
	this->times = times;
	this->type = type;
	this->num = num;
}

void Buff::draw(RenderWindow& window) {
	Object::draw(window);
}
void Buff::setPos(float x,float y) {
	Object::setPos(x, y);
}
void Buff::setScale(float x, float y) {
	Object::setScale(x, y);
}
float Buff::getScalex()
{
	return Object::getScalex();
}
float Buff::getScaley() {
	return Object::getScaley();
}