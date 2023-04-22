#pragma once
#include"Object.h"
class Role :public Object
{
public:
	Role();
	Role(Texture& texture, int width, int height, float x, float y,Texture& bg);
	~Role();
	void draw(RenderWindow& window);
	void draw(RenderWindow& window, Shader &shader);
	void setScale(float x, float y);
	void getHurt(int );
	int gethp() { return hp; }
	void Die() { isDead = true; }
protected:
	int hp;
	int atk;
	int defense;
	Sprite bg;
	bool isDead = false;
};
