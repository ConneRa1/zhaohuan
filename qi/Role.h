#pragma once
#include"Object.h"
#include"Buff.h"
class Role :public Object
{
public:
	Role();
	Role(Texture& texture, int width, int height, float x, float y,Texture& bg, EquipmentType equipmentType=EquipmentType::���ֽ�);
	~Role();
	void draw(RenderWindow& window);
	void draw(RenderWindow& window, Shader &shader);
	void setScale(float x, float y);
	void getHurt(Role*,int,bool );
	void getHurt(Role*, int);
	int getHurtNum();
	void getHurt(int);
	int gethp() { return hp; }
	bool ifDead() { return isDead; }
	void Die() { isDead = true; }
	bool checkReact(ElementType);
	ReactType doReact(ElementType);
	ElementType getElement() { return attachedElement; }
	float getX() { return x; }
	float getY() { return y; }
	void setfrozen(bool f) { isFrozen = f; }
	bool IsFrozen() { return isFrozen; }
	void addBuff(Buff buff) { buffVector.push_back(buff); return; }
	void addRelic();
	void addEquipment();
	void deleteBuff(BuffType type);
	void addHp(int i) { hp += i; if (hp > 10)hp = 10; }
protected:
	int hp;
	int atk;
	int defense;
	Sprite bg;
	bool isDead = false;
	bool isFrozen=false;
	EquipmentType equipmentType;
	int hurtNum;

	vector<Buff>buffVector;

	ElementType attachedElement=ElementType::cai;	//Ŀǰֻ�����������ֻ��һ��Ԫ��
};
