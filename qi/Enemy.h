#pragma once
#include "Role.h"
class Enemy :
	public Role
{
public:
	Enemy(Texture& texture, int width, int height, float x, float y, Texture& tbg, Texture& shp, Texture& snp, int hp = 10, int npNum = 3);
	~Enemy();
	void draw(RenderWindow& window, float x, float y, Shader& shader);
	void setScale(float x, float y);
	void move();
	void Die();
protected:
	Sprite sHp;
	vector<Sprite> sNp;
	int npNum;
	bool isMoved = false;
	bool isDead = false;
};

