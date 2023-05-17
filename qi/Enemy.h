#pragma once
#include "Role.h"
class Enemy :
	public Role
{
public:
	Enemy(Texture& texture, int width, int height, float x, float y, Texture& tbg, Texture& shp, Texture& snp, int hp, int npNum);
	~Enemy();
	void draw(RenderWindow& window, float x, float y, Shader& shader);
	void setScale(float x, float y);
	void move(); 
	void Selected(bool f);
	bool IsSelected() { return isSelected; }

};

