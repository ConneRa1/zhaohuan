#pragma once
class Game;
class State
{
public :
	State(Game* game);
	friend class Game;
	virtual void Input()=0;
	virtual void Logic()=0;
	virtual void Draw()=0;

protected:
	Game* mGame;
	int bannertime=0;
	
};

