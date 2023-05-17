#pragma once
#include"Object.h"
#include"Buff.h"
class Role :public Object
{
public:
	Role();
	Role(Texture& texture, int width, int height, float x, float y,Texture& bg);
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
	int getNp() { return currentNp; }
	int maxNp() { return npNum; }
	void setNp(int i) { currentNp = (i <= npNum ? i : npNum); updateNp(); }
	void addHp(int i) { hp += i; if (hp > 10)hp = 10; }
	void updateNp();
protected:
	int hp;
	int atk;
	int defense;
	Sprite bg;
	bool isDead = false;
	bool isFrozen=false;
	int currentNp = 0;
	int npNum;
	int hurtNum;
	Sprite sHp;
	Texture tnp0, tnp1;
	vector<Sprite> sNp;
	bool isMoved = false;
	bool isSelected = false;

	vector<Buff>buffVector;

	ElementType attachedElement=ElementType::cai;	//Ŀǰֻ�����������ֻ��һ��Ԫ��
};
