#pragma once
#include"Role.h"
#include"base.h"
class Character:public Role
{
public:
	Character(Texture& texture, int width, int height, float x, float y, Texture& tbg, Texture& shp, Texture& snp,string name,int hp=10, int npNum=3,EquipmentType equipmentType=EquipmentType::µ• ÷Ω£,ElementType elementtype=ElementType::shui);
	~Character();
	void draw(RenderWindow& window,float x,float y,Shader &shader);
	void setScale(float x, float y);
	void updateNp();
	bool isBao();
	string name;
	vector<Buff> dazhao;
};

