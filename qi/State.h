#pragma once
#include "base.h"
#include"Role.h"
class Game;
#include"Enemy.h"
class State
{
public :
	State(Game* game);
	friend class Game;
	virtual void Input()=0;
	virtual void Logic()=0;
	virtual void Draw()=0;
	virtual State* clone() { return NULL; }
protected:
	Game* mGame;
	Role* target;
	int bannertime=0;
	int hurtTimer = 0;
	int reactHurtTimer = 0;
	bool showHurt = false;
	bool showReact = false;
	int delayTimer = 0;
	int healtimer;
	int healNum;
	Role* healtarget;
};

