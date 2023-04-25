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
	bool ifDead() { return isDead; }
	void Die() { isDead = true; }
	bool checkReact(ElementType);
	ReactType doReact(ElementType);
	ElementType getElement() { return attachedElement; }
	float getX() { return x; }
	float getY() { return y; }
	void setfrozen(bool f) { isFrozen = f; }
protected:
	int hp;
	int atk;
	int defense;
	Sprite bg;
	bool isDead = false;
	bool isFrozen=false;
	ElementType attachedElement=ElementType::cai;	//目前只考虑身上最多只有一种元素
};
