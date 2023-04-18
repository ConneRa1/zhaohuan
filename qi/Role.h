#pragma once
#include"Object.h"
class Role :public Object
{
public:
	Role();
	Role(Texture& texture, int width, int height, float x, float y,Texture& bg);
	~Role();
	void triggered();
	void draw(RenderWindow& window);
	void draw(RenderWindow& window, Shader &shader);
	void setScale(float x, float y);
protected:
	int hp;
	int atk;
	int defense;
	Sprite bg;
};
