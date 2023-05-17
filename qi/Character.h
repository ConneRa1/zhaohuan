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
	void move();
	void Selected(bool);
	bool IsSelected();
	int getNp() { return currentNp; }
	int maxNp() { return npNum; }
	void setNp(int i) { currentNp = (i <= npNum ? i : npNum); cout << "np:" << currentNp << endl; updateNp(); }
	void updateNp();
	string name;
protected:
	Sprite sHp;
	Texture tnp0, tnp1;
	vector<Sprite> sNp;
	int npNum;
	int currentNp=0;
	bool isMoved = false;
	bool isSelected=false;
};

