#pragma once

#include<string>
#include<vector>
#include<SFML/Graphics.hpp>
#include<iostream>
#include<stdio.h>
using namespace std;
using namespace sf;
#define windowWidth 1920	//窗口宽度
#define windowHeight 1080	//窗口高度
#define hpWidth 0.035
#define hpHeight 0.0625
#define hpLeftOffset -0.01
#define hpUpOffset -0.01
#define npWidth 0.02 
#define npHeight 0.032
#define npLeftOffset 0.078
#define npUpOffset 0.0187
#define moveOffset 0.035
#define diceOffset 0.0386
#define abilityWidth 0.066
#define abilityHeight 0.107
#define abilityOffset 0.0623
#define abilityX 0.8105 
#define abilityY 0.885
#define cardWidth 0.086
#define cardHeight 0.26
#define cardY 0.853
#define rolldiceWidth 0.112
#define rolldiceHeight 0.160
#define rolldiceX 0.228
#define rolldiceY 0.292
#define rolldiceOffsetX 0.139
#define rolldiceOffsetY 0.225
#define confirmButtonX 0.406
#define confirmButtonY 0.855
#define confirmButtonWidth 0.186 
#define confirmButtonWidth 0.66
#define confirmButtonX 0.408
#define confirmButtonY 0.855
#define confirmButtonWidth 0.182
#define confirmButtonHeight 0.066
#define chooseCardX 0.156 
#define chooseCardY 0.356
#define chooseCardWidth  0.1054 
#define chooseCardHeight 0.288
#define chooseCardOffset 0.145
#define heldCardY 0.853
#define characterY 0.58
#define consumeDiceX 0.878  
#define consumeDiceY 0.266
#define consumeDiceOffsetX 0.055         
#define consumeDiceOffsetY 0.095
#define diceBgWidth 0.164 
#define diceBgHeight 0.8
#define diceBgX 1-0.164 
#define diceBgY 0.1
#define bannerTime 800

typedef enum CardType {		
	button,
	attack,
	cure,
	fun
};

typedef enum BuffType {		

};


