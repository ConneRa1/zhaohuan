#pragma once
#include"Role.h"
#include"base.h"
class Character:public Role
{
public:
	Character(Texture& texture, int width, int height, float x, float y, Texture& tbg, Texture& shp, Texture& snp,string name,int hp, int npNum);
	~Character();
	void draw(RenderWindow& window,float x,float y,Shader &shader);
	void setScale(float x, float y);
	void move();
	void Selected(bool);
	bool IsSelected();
	string name;
protected:
	Sprite sHp;
	vector<Sprite> sNp;
	int npNum;
	bool isMoved = false;
	bool isSelected=false;
};

