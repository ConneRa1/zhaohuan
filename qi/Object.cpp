#include"base.h"
#include "Object.h"
Object::Object()
{

}

Object::Object(Texture& texture, int width, int height,float x,float y) {
	sprite.setTexture(texture);
	sprite.scale((float)width / (float)texture.getSize().x,
		(float)height / (float)texture.getSize().y);
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	scalex = (float)width / (float)texture.getSize().x;
	scaley = (float)height / (float)texture.getSize().y;
	/*if (width != 0 && height != 0)
		sprite.setTextureRect(IntRect(0, 0, width, height));*/
}

//void Object::setPosition(int x, int y) {
//	sprite.setPosition(x, y);
//	this->x = x;
//	this->y = y;
//}

void Object::move(int x, int y) {
	sprite.move(x, y);
	this->x += x;
	this->y += y;
}
void Object::draw(RenderWindow& window) {
	sprite.setPosition(window.getSize().x * x, window.getSize().y * y);
	window.draw(sprite);
}


void Object::draw(RenderWindow& window, Shader &shader) {
	sprite.setPosition(window.getSize().x*x, window.getSize().y*y);
	window.draw(sprite,&shader);
}

bool Object::isIn(int x, int y) {
	if (x <= sprite.getPosition().x +  sprite.getTexture()->getSize().x * sprite.getScale().x && x >= sprite.getPosition().x && y <= sprite.getPosition().y + sprite.getTexture()->getSize().y * sprite.getScale().y && y >= sprite.getPosition().y)
		return true;
	return false;
}

void Object::setScale(float x, float y){
	sprite.setScale(x, y);
}
float Object::getScalex()
{
	return scalex;
}
float Object::getScaley()
{
	return scaley;
}