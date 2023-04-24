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
    font.loadFromFile("source/hk4e_zh-cn.ttf");
    bkMusic.openFromFile("source/texture/bg.wav");
    bkMusic.play();
    bkMusic.setLoop(true);
    shader.loadFromMemory("uniform sampler2D texture; uniform float brightness; void main() { vec4 color = texture2D(texture, gl_TexCoord[0].xy); color.rgb += brightness; gl_FragColor = color; }", sf::Shader::Fragment);
    shader.setUniform("texture", sf::Shader::CurrentTexture);
    

	gameOver = false;
	gameQuit = false;

    mState = new ChooseCardState(this);

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
    texarr[91].loadFromFile("source/texture/costPoint.png");
    ui.push_back(UI(texarr[91], int(0.0323 * windowWidth), int(0.06 * windowHeight), 0.945, 0.042, "costPoint"));
    texarr[91].loadFromFile("source/texture/enemyturn.png");
    texarr[92].loadFromFile("source/texture/playerturn.png");
    texarr[93].loadFromFile("source/texture/投掷阶段.png");
    texarr[94].loadFromFile("source/texture/endstate.png");
    enemybanner = Object(texarr[91], windowWidth, windowHeight, 0, 0);
    playerbanner = Object(texarr[92], windowWidth, windowHeight, 0, 0);
    whenDice = Object(texarr[93], windowWidth, windowHeight, 0, 0);
    whenEnd = Object(texarr[94], windowWidth, windowHeight, 0, 0);
    texarr[95].loadFromFile("source/texture/change.png");
    texarr[96].loadFromFile("source/texture/changeconfirm.png");
    texarr[97].loadFromFile("source/texture/target.png");
    texarr[98].loadFromFile("source/texture/hurt.png");
    changeConfirm = Object(texarr[96], 106, 130, changeConfirmX, changeConfirmY);
    changeTarget= Object(texarr[95], 163,261, 0, 0);    //放角色卡左上角
    target = Object(texarr[97], 163, 261, 0, 0);
    hurt= Object(texarr[98], 189, 255, 0, 0);

    //200号骰子
    Object o1;
    texarr[200].loadFromFile("source/texture/dice/dice0.png");
    chooseDice = Object(texarr[200], 80, 92, 0, 0);
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
    texarr[299].loadFromFile("source/texture/chupai.png");
    chupai = Object(texarr[299], windowWidth * confirmButtonWidth, windowHeight * confirmButtonHeight, confirmButtonX, confirmButtonY);
    texarr[298].loadFromFile("source/texture/dicebg.png");
    dicebg = Object(texarr[298], windowWidth * diceBgWidth, windowHeight * diceBgHeight, diceBgX, diceBgY);
    //初始选卡
    texarr[301].loadFromFile("source/texture/loadingcard.png");
    texarr[302].loadFromFile("source/texture/eventcard/card1.png");
    cards.push_back(new Card(texarr[301], windowWidth * chooseCardWidth, windowHeight * chooseCardHeight, chooseCardX, chooseCardY,Cost(1,pair<ElementType,int>(ElementType::cai,2)),CardType::null,true));
    cards.push_back(new Card(texarr[301], windowWidth * chooseCardWidth, windowHeight * chooseCardHeight, chooseCardX, chooseCardY, Cost(1, pair<ElementType, int>(ElementType::cai, 2)), CardType::null,true));
    cards.push_back(new Card(texarr[301], windowWidth * chooseCardWidth, windowHeight * chooseCardHeight, chooseCardX, chooseCardY, Cost(1, pair<ElementType, int>(ElementType::cai, 2)), CardType::null,true));
    cards.push_back(new Card(texarr[301], windowWidth * chooseCardWidth, windowHeight * chooseCardHeight, chooseCardX, chooseCardY, Cost(1, pair<ElementType, int>(ElementType::cai, 2)), CardType::null,true));
    cards.push_back(new Card(texarr[301], windowWidth * chooseCardWidth, windowHeight * chooseCardHeight, chooseCardX, chooseCardY, Cost(1, pair<ElementType, int>(ElementType::cai, 2)), CardType::null,true));
    cards.push_back(new Card(texarr[302], windowWidth * chooseCardWidth, windowHeight * chooseCardHeight, chooseCardX, chooseCardY, Cost(1, pair<ElementType, int>(ElementType::cai, 2)), CardType::null));
    cards.push_back(new Card(texarr[302], windowWidth * chooseCardWidth, windowHeight * chooseCardHeight, chooseCardX, chooseCardY, Cost(1, pair<ElementType, int>(ElementType::cai, 2)), CardType::null));
    cards.push_back(new Card(texarr[302], windowWidth * chooseCardWidth, windowHeight * chooseCardHeight, chooseCardX, chooseCardY, Cost(1, pair<ElementType, int>(ElementType::cai, 2)), CardType::null));

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
    //加载所有技能
    abilityVector.push_back(new Ability(ElementType::shui,2,texarr[150], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 0, abilityY, Cost(1, pair<ElementType, int>(ElementType::cai, 3))));
    abilityVector.push_back(new Ability(ElementType::shui, 2, texarr[151], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 1, abilityY, Cost(1, pair<ElementType, int>(ElementType::cai,3))));
    abilityVector.push_back(new Ability(ElementType::shui, 2, texarr[152], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 2, abilityY, Cost(1, pair<ElementType, int>(ElementType::cai, 3))));

    abilityVector.push_back(new Ability(ElementType::lei, 2, texarr[153], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 0, abilityY, Cost(1, pair<ElementType, int>(ElementType::cai, 3))));
    abilityVector.push_back(new Ability(ElementType::lei, 2, texarr[154], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 1, abilityY, Cost(1, pair<ElementType, int>(ElementType::cai, 3))));
    abilityVector.push_back(new Ability(ElementType::lei, 2, texarr[155], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 2, abilityY, Cost(1, pair<ElementType, int>(ElementType::cai, 3))));

    abilityVector.push_back(new Ability(ElementType::bing, 2, texarr[156], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 0, abilityY, Cost(1, pair<ElementType, int>(ElementType::cai, 3))));
    abilityVector.push_back(new Ability(ElementType::bing, 2, texarr[157], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 1, abilityY, Cost(1, pair<ElementType, int>(ElementType::cai, 3))));
    abilityVector.push_back(new Ability(ElementType::bing, 2, texarr[158], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 2, abilityY, Cost(1, pair<ElementType, int>(ElementType::cai, 3))));

    for(int i=0;i<3;i++)
        sAbility.push_back(abilityVector[i]);

    diceNum = Cost(4, pair<ElementType, int>(ElementType::bing, 0), pair<ElementType, int>(ElementType::lei, 0),
        pair<ElementType, int>(ElementType::shui, 0), pair<ElementType, int>(ElementType::cai, 8));
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