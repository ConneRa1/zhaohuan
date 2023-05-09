#pragma once
#include "base.h"
#include<SFML/Graphics.hpp>

using namespace sf;

class Object {		//可显示物体的共有父类
public:
	Object();
	Object(Texture& texture, int width = 0, int height = 0, float x = 0, float y = 0);	//会把整个texture全部加载，其中width，height是精灵大小
	void setPos(float x, float y);//设定位置，不设置则默认为0;
	void move(int x, int y);  //移动
	//Sprite getSprite() const;	//返回sprite，便于显示
	void setScale(float x, float y);
	void draw(RenderWindow& window);
	void draw(RenderWindow& window,Shader& shader);		//在window中显示这个物体
	bool isIn(int x, int y);	//判断是否在范围内
	float getScalex();
	float getScaley();
	Sprite sprite;
	float getPosX() { return x; }
	float getPosY() { return y; }
protected:
	float x, y;
	int width, height;
	float scalex, scaley;
};