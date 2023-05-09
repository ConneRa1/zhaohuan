#include "Memento.h"
#include"Game.h"
Memento::Memento(State* s, Game* game) 
{
	characterVector=game->characterVector;
	enemyVector = game->enemyVector;
	cards = game->cards;
	diceNum = game->diceNum;
	firstInitDice=  game->firstInitDice;
	firstConfirm = game->firstConfirm;
	 playerTurnOver =  game->playerTurnOver;
	enemyTurnOver = game->enemyTurnOver;
	 enemyAction = game->enemyAction;
	 isWin =  game->isWin;
	 initdice =  game->initdice;
	isPlayerFirst =game->isPlayerFirst;
	save =s->clone();
}