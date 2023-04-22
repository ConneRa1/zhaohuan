#include"Game.h"

void Game:: toggleFullscreen() {
    isFullscreen = !isFullscreen;
    if (isFullscreen) {
        // 如果当前状态是窗口化，则将窗口状态设置为全屏
        window.create(VideoMode::getFullscreenModes()[0], "My Game", Style::Fullscreen);
    }
    else {
        // 如果当前状态是全屏，则将窗口状态设置为窗口化
        window.create(VideoMode(windowWidth,windowHeight), "My Game", Style::Default);
    }
    
}
Game::Game() {
    //view=View(FloatRect(0.f, 0.f, windowWidth, windowHeight));
    view=View(Vector2f(0.f, 0.f), Vector2f(windowWidth, windowHeight));
	window.create(VideoMode(windowWidth, windowHeight), L"xx");
    auto modes = VideoMode::getFullscreenModes();

    view.setSize(Vector2f(window.getSize()));
    view.setCenter(Vector2f(window.getSize()) / 2.f);
    window.setView(view);
    view.setViewport(FloatRect(0.f, 0.f, 1.f, 1.f));
}

Game::~Game() {

}

void Game::Run() {
	do
	{

		Initial();
		while (window.isOpen() && gameOver == false)
		{
			Input();
			Logic();
			Draw();
		}
	} while (window.isOpen() && !gameQuit);
}

void Game::Initial() {
    bkMusic.openFromFile("source/texture/bg.wav");
    bkMusic.play();
    bkMusic.setLoop(true);
    shader.loadFromMemory("uniform sampler2D texture; uniform float brightness; void main() { vec4 color = texture2D(texture, gl_TexCoord[0].xy); color.rgb += brightness; gl_FragColor = color; }", sf::Shader::Fragment);
    shader.setUniform("texture", sf::Shader::CurrentTexture);
    

	gameOver = false;
	gameQuit = false;

    mState = new PlayerTurnState(this);

	tBackGround.loadFromFile("source/texture/bg.png");
    backGround = Object(tBackGround, windowWidth, windowHeight,0,0);

    texarr[0].loadFromFile("source/texture/high.png");
    UI c;
    c = UI(texarr[0], 340,60,  0.012,  0.006,"high");
    ui.push_back(c);
    UI c1;
    texarr[1].loadFromFile("source/texture/low.png");
    c1 = UI(texarr[1], 340, 70,  0.013,  0.89,"low");
    ui.push_back(c1);
    UI c2;
    texarr[90].loadFromFile("source/texture/turnMark.png");
    c2= UI(texarr[90], 148, 296, 0.0, 0.3588, "turnMark");
    ui.push_back(c2);
    UI c3;
    texarr[91].loadFromFile("source/texture/costPoint.png");
    c3 = UI(texarr[91], int(0.0323*windowWidth),int(0.06*windowHeight), 0.945 ,0.042,"costPoint");
    ui.push_back(c3);

    //200号骰子
    Object o1;
    texarr[200].loadFromFile("source/texture/dice/dice0.png");
    o1 = Object(texarr[200], 40,42, 0.963, 0.13);
    dices.push_back(o1);
    o1 = Object(texarr[200], 40,42, 0.963, 0.13+diceOffset);
    dices.push_back(o1);
    o1 = Object(texarr[200], 40,42, 0.963, 0.13 + 2*diceOffset);
    dices.push_back(o1);
    o1 = Object(texarr[200], 40,42, 0.963, 0.13 + 3*diceOffset);
    dices.push_back(o1);
    o1 = Object(texarr[200], 40,42, 0.963, 0.13 + 4*diceOffset);
    dices.push_back(o1);
    o1 = Object(texarr[200], 40,42, 0.963, 0.13 + 5*diceOffset);
    dices.push_back(o1);
    o1 = Object(texarr[200], 40,42, 0.963, 0.13 + 6*diceOffset);
    dices.push_back(o1);
    o1 = Object(texarr[200], 40,42, 0.963, 0.13 + 7*diceOffset);
    dices.push_back(o1);

    texarr[210].loadFromFile("source/texture/rolldice0.png");
    rollDices.push_back(Object(texarr[210], windowWidth * rolldiceWidth, windowHeight * rolldiceHeight, rolldiceX, rolldiceY));
    rollDices.push_back(Object(texarr[210], windowWidth * rolldiceWidth, windowHeight * rolldiceHeight, rolldiceX+1*rolldiceOffsetX, rolldiceY));
    rollDices.push_back(Object(texarr[210], windowWidth * rolldiceWidth, windowHeight * rolldiceHeight, rolldiceX+2*rolldiceOffsetX, rolldiceY));
    rollDices.push_back(Object(texarr[210], windowWidth * rolldiceWidth, windowHeight * rolldiceHeight, rolldiceX+3*rolldiceOffsetX, rolldiceY));
    rollDices.push_back(Object(texarr[210], windowWidth * rolldiceWidth, windowHeight * rolldiceHeight, rolldiceX, rolldiceY+1*rolldiceOffsetY));
    rollDices.push_back(Object(texarr[210], windowWidth * rolldiceWidth, windowHeight * rolldiceHeight, rolldiceX + 1 * rolldiceOffsetX, rolldiceY+1*rolldiceOffsetY));
    rollDices.push_back(Object(texarr[210], windowWidth * rolldiceWidth, windowHeight * rolldiceHeight, rolldiceX + 2 * rolldiceOffsetX, rolldiceY+1*rolldiceOffsetY));
    rollDices.push_back(Object(texarr[210], windowWidth * rolldiceWidth, windowHeight * rolldiceHeight, rolldiceX + 3 * rolldiceOffsetX, rolldiceY+1*rolldiceOffsetY));

    //确认按钮
    texarr[300].loadFromFile("source/texture/confirmButton.png");
    confirmButton = Object(texarr[300], windowWidth * confirmButtonWidth, windowHeight * confirmButtonHeight, confirmButtonX, confirmButtonY);
    //初始选卡
    texarr[301].loadFromFile("source/texture/loadingcard.png");
    texarr[302].loadFromFile("source/texture/eventcard/card1.png");
    cards.push_back(new Card(texarr[301], windowWidth * chooseCardWidth, windowHeight * chooseCardHeight, chooseCardX, chooseCardY,0,true));
    cards.push_back(new Card(texarr[301], windowWidth * chooseCardWidth, windowHeight * chooseCardHeight, chooseCardX, chooseCardY,0,true));
    cards.push_back(new Card(texarr[301], windowWidth * chooseCardWidth, windowHeight * chooseCardHeight, chooseCardX, chooseCardY,0,true));
    cards.push_back(new Card(texarr[301], windowWidth * chooseCardWidth, windowHeight * chooseCardHeight, chooseCardX, chooseCardY,0,true));
    cards.push_back(new Card(texarr[301], windowWidth * chooseCardWidth, windowHeight * chooseCardHeight, chooseCardX, chooseCardY,0,true));
    cards.push_back(new Card(texarr[302], windowWidth * chooseCardWidth, windowHeight * chooseCardHeight, chooseCardX, chooseCardY, 2));
    cards.push_back(new Card(texarr[302], windowWidth * chooseCardWidth, windowHeight * chooseCardHeight, chooseCardX, chooseCardY, 2));
    cards.push_back(new Card(texarr[302], windowWidth * chooseCardWidth, windowHeight * chooseCardHeight, chooseCardX, chooseCardY, 2));

    for (int i = 0; i < 5; i++)
    {
        cards.drawCard();//抽卡
    }

    //100后技能
    texarr[100].loadFromFile("source/texture/kuang.png");
    texarr[101].loadFromFile("source/texture/hp.png");
    texarr[102].loadFromFile("source/texture/np0.png");
    texarr[103].loadFromFile("source/texture/np1.png");
    texarr[150].loadFromFile("source/texture/character/ability/xingqiu_a.png");
    texarr[151].loadFromFile("source/texture/character/ability/xingqiu_e.png");
    texarr[152].loadFromFile("source/texture/character/ability/xingqiu_q.png");
    texarr[153].loadFromFile("source/texture/character/ability/keqing_a.png");
    texarr[154].loadFromFile("source/texture/character/ability/keqing_e.png");
    texarr[155].loadFromFile("source/texture/character/ability/keqing_q.png");
    texarr[156].loadFromFile("source/texture/character/ability/kaiya_a.png");
    texarr[157].loadFromFile("source/texture/character/ability/kaiya_e.png");
    texarr[158].loadFromFile("source/texture/character/ability/kaiya_q.png");

    texarr[2].loadFromFile("source/texture/character/xingqiu.png");
    Character a1 = Character(texarr[2], cardWidth* windowWidth, cardHeight* windowHeight, 0.343, 0.58,texarr[100], texarr[101], texarr[102],"xingqiu",10,2);
    //a1.Die();
    a1.Selected(true);
    characterVector.push_back(a1);
    texarr[3].loadFromFile("source/texture/character/keqing.png");
    Character a2 = Character(texarr[3], cardWidth * windowWidth, cardHeight * windowHeight, 0.457, 0.58, texarr[100], texarr[101], texarr[102],"keqing",10,3);
    characterVector.push_back(a2);
    a2.Die();
    texarr[4].loadFromFile("source/texture/character/kaiya.png");
    Character a3 = Character(texarr[4], cardWidth * windowWidth, cardHeight * windowHeight, 0.57, 0.58, texarr[100], texarr[101], texarr[102],"kaiya",10,2);
    characterVector.push_back(a3);

    texarr[5].loadFromFile("source/texture/enemy/enemy1.png");
    Enemy e = Enemy(texarr[5], cardWidth * windowWidth, cardHeight * windowHeight, 0.457, 0.152, texarr[100], texarr[101], texarr[102],10,3);
    enemyVector.push_back(e);

    
    sAbility.push_back(Card(texarr[150], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 0, abilityY, 3));
    sAbility.push_back(Card(texarr[151], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 1, abilityY, 3));
    sAbility.push_back(Card(texarr[152], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 2, abilityY, 3));
}

void Game::Draw() {
    mState->Draw();
}

void Game::Input() {
    mState->Input();
}

void Game::Logic() {
    mState->Logic();
}


void  Game::ChangeState(State* state)
{
    delete(mState);
    mState = state;
}