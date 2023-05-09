#pragma once
#include "base.h"
#include<SFML/Graphics.hpp>

using namespace sf;

class Object {		//����ʾ����Ĺ��и���
public:
	Object();
	Object(Texture& texture, int width = 0, int height = 0, float x = 0, float y = 0);	//�������textureȫ�����أ�����width��height�Ǿ����С
	void setPos(float x, float y);//�趨λ�ã���������Ĭ��Ϊ0;
	void move(int x, int y);  //�ƶ�
	//Sprite getSprite() const;	//����sprite��������ʾ
	void setScale(float x, float y);
	void draw(RenderWindow& window);
	void draw(RenderWindow& window,Shader& shader);		//��window����ʾ�������
	bool isIn(int x, int y);	//�ж��Ƿ��ڷ�Χ��
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