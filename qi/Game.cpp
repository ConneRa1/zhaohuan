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
    /*cout << "选择敌人数目：" << endl;
    cin >> enemyNum;*/
    enemyNum = 3;
    font.loadFromFile("source/hk4e_zh-cn.ttf");
    bkMusic.openFromFile("source/texture/bg.wav");
    bkMusic.play();
    bkMusic.setLoop(true);
    shader.loadFromMemory("uniform sampler2D texture; uniform float brightness; uniform float blue; void main() { vec4 color = texture2D(texture, gl_TexCoord[0].xy); color.rgb += brightness;color.b+=blue; gl_FragColor = color; }", sf::Shader::Fragment);
    shader.setUniform("texture", sf::Shader::CurrentTexture);
    

	gameOver = false;
	gameQuit = false;

    mState = new FirstDiceState(this);

    vector<Place> p1;
    playerPlaceVector.push_back(p1);
    vector<Place> p2;
    playerPlaceVector.push_back(p2);
    vector<Place> p3;
    playerPlaceVector.push_back(p3);
    vector<Place> p4;
    playerPlaceVector.push_back(p4);

    vector<Place> e1;
    playerPlaceVector.push_back(e1);
    vector<Place> e2;
    playerPlaceVector.push_back(e2);
    vector<Place> e3;
    playerPlaceVector.push_back(e3);
    vector<Place> e4;
    playerPlaceVector.push_back(e4);


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
    changeTarget = Object(texarr[95], 163, 261, 0, 0);    //放角色卡左上角
    target = Object(texarr[97], 163, 261, 0, 0);
    hurt = Object(texarr[98], 189, 255, 0, 0);

    //200号骰子
    Object o1;
    texarr[200].loadFromFile("source/texture/dice/dice0.png");
    texarr[201].loadFromFile("source/texture/dice/dice1.png");
    texarr[202].loadFromFile("source/texture/dice/dice2.png");
    texarr[203].loadFromFile("source/texture/dice/dice3.png");
    texarr[204].loadFromFile("source/texture/dice/dice4.png");
    texarr[205].loadFromFile("source/texture/dice/dice5.png");
    texarr[206].loadFromFile("source/texture/dice/dice6.png");
    texarr[207].loadFromFile("source/texture/dice/dice7.png");

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
    //210以后绑骰子
    texarr[210].loadFromFile("source/texture/rolldice0.png");
    texarr[211].loadFromFile("source/texture/rolldice1.png");
    texarr[212].loadFromFile("source/texture/rolldice2.png");
    texarr[213].loadFromFile("source/texture/rolldice3.png");
    texarr[214].loadFromFile("source/texture/rolldice4.png");
    texarr[215].loadFromFile("source/texture/rolldice5.png");
    texarr[216].loadFromFile("source/texture/rolldice6.png");
    texarr[217].loadFromFile("source/texture/rolldice7.png");

    rollDices.push_back(Object(texarr[210], windowWidth * rolldiceWidth, windowHeight * rolldiceHeight, rolldiceX, rolldiceY));
    rollDices.push_back(Object(texarr[210], windowWidth * rolldiceWidth, windowHeight * rolldiceHeight, rolldiceX+1*rolldiceOffsetX, rolldiceY));
    rollDices.push_back(Object(texarr[210], windowWidth * rolldiceWidth, windowHeight * rolldiceHeight, rolldiceX+2*rolldiceOffsetX, rolldiceY));
    rollDices.push_back(Object(texarr[210], windowWidth * rolldiceWidth, windowHeight * rolldiceHeight, rolldiceX+3*rolldiceOffsetX, rolldiceY));
    rollDices.push_back(Object(texarr[210], windowWidth * rolldiceWidth, windowHeight * rolldiceHeight, rolldiceX, rolldiceY+1*rolldiceOffsetY));
    rollDices.push_back(Object(texarr[210], windowWidth * rolldiceWidth, windowHeight * rolldiceHeight, rolldiceX + 1 * rolldiceOffsetX, rolldiceY+1*rolldiceOffsetY));
    rollDices.push_back(Object(texarr[210], windowWidth * rolldiceWidth, windowHeight * rolldiceHeight, rolldiceX + 2 * rolldiceOffsetX, rolldiceY+1*rolldiceOffsetY));
    rollDices.push_back(Object(texarr[210], windowWidth * rolldiceWidth, windowHeight * rolldiceHeight, rolldiceX + 3 * rolldiceOffsetX, rolldiceY+1*rolldiceOffsetY));
    //220以后绑元素
    texarr[220].loadFromFile("source/texture/element/huo.png");
    texarr[221].loadFromFile("source/texture/element/shui.png");
    texarr[222].loadFromFile("source/texture/element/bing.png");
    texarr[223].loadFromFile("source/texture/element/cao.png");
    texarr[224].loadFromFile("source/texture/element/yan.png");
    texarr[225].loadFromFile("source/texture/element/lei.png");
    texarr[226].loadFromFile("source/texture/element/feng.png");
    shui= Object(texarr[221], 40, 40, 0,0);
    lei = Object(texarr[225], 40, 40, 0, 0);
    bing = Object(texarr[222], 40, 40, 0, 0);
    huo = Object(texarr[220], 40, 40, 0, 0);
    yan = Object(texarr[224], 40, 40, 0, 0);
    feng = Object(texarr[226], 40, 40, 0, 0);
    cao = Object(texarr[223], 40, 40, 0, 0);
    //230以后绑骰子的框
    texarr[230].loadFromFile("source/texture/diceTriggerred.png");
    for (int i = 0; i < 4; i++)
    {
        diceTriggerred[i] = Object(texarr[230], 90, 95, 0, 0);
    }
    texarr[231].loadFromFile("source/texture/rolldiceTriggered.png");
    for (int i = 0; i < 8; i++)
    {
        rollDicesbg[i] = Object(texarr[231], windowWidth * rolldiceWidth, windowHeight * rolldiceHeight, 0, 0);
    }
    

    //确认按钮
    texarr[300].loadFromFile("source/texture/confirmButton.png");
    confirmButton = Object(texarr[300], windowWidth * confirmButtonWidth, windowHeight * confirmButtonHeight, confirmButtonX, confirmButtonY);
    texarr[299].loadFromFile("source/texture/chupai.png");
    chupai = Object(texarr[299], windowWidth * confirmButtonWidth, windowHeight * confirmButtonHeight, confirmButtonX, confirmButtonY);
    texarr[298].loadFromFile("source/texture/dicebg.png");
    dicebg = Object(texarr[298], windowWidth * diceBgWidth, windowHeight * diceBgHeight, diceBgX, diceBgY);
    //初始选卡
    //texarr[301].loadFromFile("source/texture/loadingcard.png");
    texarr[301].loadFromFile("source/texture/eventcard/card1.png");
    texarr[302].loadFromFile("source/texture/eventcard/5.png");
    texarr[303].loadFromFile("source/texture/foodcard/1.png");
    texarr[304].loadFromFile("source/texture/foodcard/2.png");
    texarr[305].loadFromFile("source/texture/foodcard/3.png");
    texarr[306].loadFromFile("source/texture/eventcard/1.png");
    texarr[307].loadFromFile("source/texture/placecard/1.png");
    texarr[308].loadFromFile("source/texture/placecard/3.png");
    texarr[309].loadFromFile("source/texture/placecard/4.png");
    texarr[310].loadFromFile("source/texture/placecard/5.png");
    texarr[311].loadFromFile("source/texture/placecard/6.png");
    texarr[312].loadFromFile("source/texture/placecard/8.png");
    texarr[313].loadFromFile("source/texture/placecard/11.png");
    texarr[314].loadFromFile("source/texture/placecard/12.png");
    texarr[315].loadFromFile("source/texture/placecard/13.png");
    texarr[316].loadFromFile("source/texture/placecard/14.png");
    texarr[317].loadFromFile("source/texture/placecard/15.png");
    texarr[318].loadFromFile("source/texture/eventcard/3.png");
    texarr[319].loadFromFile("source/texture/eventcard/4.png");
    texarr[320].loadFromFile("source/texture/eventcard/6.png");
    texarr[321].loadFromFile("source/texture/eventcard/7.png");
    texarr[322].loadFromFile("source/texture/sth/2.png");
    texarr[323].loadFromFile("source/texture/sth/3.png");
    texarr[324].loadFromFile("source/texture/sth/5.png");



    Card* u1 = CardFactory::CreateCard(texarr[301], 2, CardType::event, ConcreateCard::最好的伙伴, true);
    //Card* u1 = CardFactory::CreateCard(texarr[301], 1, CardType::relics, ConcreateCard::酒渍船帽, false);
    Card* u2 = CardFactory::CreateCard(texarr[302], 1, CardType::event, ConcreateCard::交给我吧,true);
    Card* u3 = CardFactory::CreateCard(texarr[303], 2, CardType::event, ConcreateCard::仙跳墙,false);
    Card* u4 = CardFactory::CreateCard(texarr[304], 1, CardType::event, ConcreateCard::土豆饼, false);
    Card* u5 = CardFactory::CreateCard(texarr[305], 0, CardType::event, ConcreateCard::烧鸡, false);
    Card* u6 = CardFactory::CreateCard(texarr[306], 1, CardType::event, ConcreateCard::白垩之术, true);
    Card* u7 = CardFactory::CreateCard(texarr[307], 3, CardType::place, ConcreateCard::派蒙, true);
    Card* u8 = CardFactory::CreateCard(texarr[308], 2, CardType::place, ConcreateCard::西风大教堂, true);
    Card* u9 = CardFactory::CreateCard(texarr[309], 0, CardType::place, ConcreateCard::立本 , true);
    Card* u10 = CardFactory::CreateCard(texarr[310], 2, CardType::place, ConcreateCard::望舒客栈,  true);
    Card* u11 = CardFactory::CreateCard(texarr[311], 1, CardType::place, ConcreateCard::刘苏 , true);
    Card* u12 = CardFactory::CreateCard(texarr[312], 2, CardType::place, ConcreateCard::璃月港口 , true);
    Card* u13= CardFactory::CreateCard(texarr[313], 2, CardType::place, ConcreateCard::参量质变仪, true);
    Card* u14= CardFactory::CreateCard(texarr[314], 1, CardType::place, ConcreateCard::凯瑟琳, true);
    Card* u15 = CardFactory::CreateCard(texarr[315], 1, CardType::place, ConcreateCard::常九爷 , true);
    Card* u16 = CardFactory::CreateCard(texarr[316], 2, CardType::place, ConcreateCard::骑士团图书馆, true);
    Card* u17 = CardFactory::CreateCard(texarr[317], 1, CardType::place, ConcreateCard::晨曦酒庄, true);
    Card* u18 = CardFactory::CreateCard(texarr[318], 1, CardType::event, ConcreateCard::无中生有, true);
    Card* u19 = CardFactory::CreateCard(texarr[319], 2, CardType::event, ConcreateCard::莫娜, true);
    Card* u20 = CardFactory::CreateCard(texarr[320], 1, CardType::event, ConcreateCard::鹤归, true);
    Card* u21 = CardFactory::CreateCard(texarr[321], 0, CardType::event, ConcreateCard::罗莎莉亚, true);
    Card* u22 = CardFactory::CreateCard(texarr[322], 1, CardType::relics, ConcreateCard::破冰踏雪的回音, false);
    Card* u23 = CardFactory::CreateCard(texarr[323], 1, CardType::relics, ConcreateCard::酒渍船帽, false);
    Card* u24 = CardFactory::CreateCard(texarr[324], 1, CardType::relics, ConcreateCard::唤雷的头冠, false);


    
    cards.push_back(u1->clone());
    cards.push_back(u2->clone());
    cards.push_back(u6->clone());
    cards.push_back(u3->clone());
    cards.push_back(u4->clone());
    cards.push_back(u5->clone());
    cards.push_back(u7->clone());
    cards.push_back(u8->clone());
    cards.push_back(u9->clone());
    cards.push_back(u10->clone());
    cards.push_back(u11->clone());
    cards.push_back(u12->clone());
    cards.push_back(u13->clone());
    cards.push_back(u14->clone());
    cards.push_back(u15->clone());
    cards.push_back(u16->clone());
    cards.push_back(u17->clone());
    cards.push_back(u18->clone());
    cards.push_back(u19->clone());
    cards.push_back(u20->clone());
    cards.push_back(u21->clone());
    cards.push_back(u22->clone());
    cards.push_back(u23->clone());
    cards.push_back(u24->clone());



    for (int i = 0; i < 5; i++)
    {
        cards.drawCard();//抽卡
    }

     //350后绑场景的小图标
    texarr[350].loadFromFile("source/texture/place/place.png");

    addPlayerPlace(Place(PlaceType::投掷, ConcreateCard::骑士团图书馆, 1, 1, windowWidth * placeCardWidth, windowHeight * placeCardHeight, texarr[350]));
    addPlayerPlace(Place(PlaceType::结束, ConcreateCard::西风大教堂, 1, 2, windowWidth * placeCardWidth, windowHeight * placeCardHeight, texarr[350]));
    //addEnemyPlace(Place(PlaceType::结束, ConcreateCard::西风大教堂, 1, 1, windowWidth * placeCardWidth, windowHeight * placeCardHeight, texarr[350]));
   //100 人物框
    texarr[100].loadFromFile("source/texture/kuang.png");
    texarr[101].loadFromFile("source/texture/hp.png");
    texarr[102].loadFromFile("source/texture/np0.png");
    texarr[103].loadFromFile("source/texture/np1.png");
    //110以后buff
    texarr[110].loadFromFile("source/texture/盾.png");
    texarr[111].loadFromFile("source/texture/攻.png");
    texarr[112].loadFromFile("source/texture/饱.png");

     //150后技能
    texarr[150].loadFromFile("source/texture/character/ability/xingqiu_a.png");
    texarr[151].loadFromFile("source/texture/character/ability/xingqiu_e.png");
    texarr[152].loadFromFile("source/texture/character/ability/xingqiu_q.png");
    texarr[153].loadFromFile("source/texture/character/ability/keqing_a.png");
    texarr[154].loadFromFile("source/texture/character/ability/keqing_e.png");
    texarr[155].loadFromFile("source/texture/character/ability/keqing_q.png");
    texarr[156].loadFromFile("source/texture/character/ability/kaiya_a.png");
    texarr[157].loadFromFile("source/texture/character/ability/kaiya_e.png");
    texarr[158].loadFromFile("source/texture/character/ability/kaiya_q.png");
    texarr[160].loadFromFile("source/texture//ability/1_a.png");
    texarr[161].loadFromFile("source/texture//ability/1_e.png");
    texarr[162].loadFromFile("source/texture//ability/1_q.png");
    texarr[163].loadFromFile("source/texture//ability/2_a.png");
    texarr[164].loadFromFile("source/texture//ability/2_e.png");
    texarr[165].loadFromFile("source/texture//ability/2_q.png");
    texarr[166].loadFromFile("source/texture//ability/3_a.png");
    texarr[167].loadFromFile("source/texture//ability/3_e.png");
    texarr[168].loadFromFile("source/texture//ability/3_q.png");

    //heal
    texarr[170].loadFromFile("source/texture/heal1.png");
    texarr[171].loadFromFile("source/texture/heal2.png");
    heal1 = Object(texarr[170], windowWidth * cardWidth, windowHeight * cardHeight, 0, 0);
    heal2 = Object(texarr[171], windowWidth * cardWidth, windowHeight * cardHeight, 0, 0);

    for (int i = 0; i < 9; i++)
    {
        abilityBanner[i] = Object(texarr[160 + i], windowWidth, windowHeight, 0, 0);
    }

    texarr[2].loadFromFile("source/texture/character/xingqiu.png");
    Character a1 = Character(texarr[2], cardWidth* windowWidth, cardHeight* windowHeight, 0.343, 0.58,texarr[100], texarr[101], texarr[102],"xingqiu",10,2,EquipmentType::大剑,ElementType::shui);
    a1.Selected(true,true);
    a1.addBuff(Buff(1, BuffType::盾, 2,36,36, texarr[110]));
    a1.addBuff(Buff(1, BuffType::加攻, 2, 36, 36, texarr[111]));
    a1.addBuff(Buff(1, BuffType::饱, 1, 36, 36, texarr[112]));
    a1.addBuff(Buff(1, BuffType::大招, 1, 36, 36, texarr[111]));
    cout << int(a1.getElementType()) << endl;
    characterVector.push_back(a1);
    texarr[3].loadFromFile("source/texture/character/keqing.png");
    Character a2 = Character(texarr[3], cardWidth * windowWidth, cardHeight * windowHeight, 0.457, 0.58, texarr[100], texarr[101], texarr[102],"keqing",10,3, EquipmentType::单手剑, ElementType::lei);
    characterVector.push_back(a2);
    texarr[4].loadFromFile("source/texture/character/kaiya.png");
    Character a3 = Character(texarr[4], cardWidth * windowWidth, cardHeight * windowHeight, 0.57, 0.58, texarr[100], texarr[101], texarr[102],"kaiya",10,2, EquipmentType::单手剑, ElementType::bing);
    characterVector.push_back(a3);

    texarr[5].loadFromFile("source/texture/enemy/enemy1.png");
    Enemy e = Enemy(texarr[5], cardWidth * windowWidth, cardHeight * windowHeight, 0.457, 0.152, texarr[100], texarr[101], texarr[102],10,3);
    for (int it = 0; it < enemyNum; it++)
    {
        enemyVector.push_back(e);
    }
    float initX = 0.5-(enemyVector.size()*cardWidth+(enemyVector.size()-1)*cardOffset)/2.0f;
    for (int it = 0; it < enemyVector.size(); it++)
    {
        enemyVector[it].setPos(initX + cardWidth*it+ cardOffset*it, 0.152);
    }
    enemyVector[enemyVector.size() / 2].Selected(true, false);
    
    //加载所有技能
    abilityVector.push_back(new Ability(ElementType::cai,2,texarr[150], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 0, abilityY, Cost(1, pair<ElementType, int>(ElementType::cai, 3))));
    abilityVector.push_back(new Ability(ElementType::shui, 3, texarr[151], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 1, abilityY, Cost(1, pair<ElementType, int>(ElementType::cai,3))));
    abilityVector.push_back(new Ability(ElementType::shui, 3, texarr[152], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 2, abilityY, Cost(1, pair<ElementType, int>(ElementType::shui, 3))));

    abilityVector.push_back(new Ability(ElementType::cai, 2, texarr[153], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 0, abilityY, Cost(1, pair<ElementType, int>(ElementType::cai, 3))));
    abilityVector.push_back(new Ability(ElementType::lei, 3, texarr[154], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 1, abilityY, Cost(1, pair<ElementType, int>(ElementType::cai, 3))));
    abilityVector.push_back(new Ability(ElementType::lei, 3, texarr[155], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 2, abilityY, Cost(1, pair<ElementType, int>(ElementType::lei, 3))));

    abilityVector.push_back(new Ability(ElementType::cai, 2, texarr[156], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 0, abilityY, Cost(1, pair<ElementType, int>(ElementType::cai, 3))));
    abilityVector.push_back(new Ability(ElementType::bing, 3, texarr[157], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 1, abilityY, Cost(1, pair<ElementType, int>(ElementType::cai, 3))));
    abilityVector.push_back(new Ability(ElementType::bing, 3, texarr[158], windowWidth * abilityWidth, windowHeight * abilityHeight, abilityX + abilityOffset * 2, abilityY, Cost(1, pair<ElementType, int>(ElementType::bing, 3))));

    for(int i=0;i<3;i++)
        sAbility.push_back(abilityVector[i]);

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

void Game::showElement(Role it)
{
    switch (it.getElement())
    {
    case ElementType::shui:
        shui.setPos(it.getX() + cardWidth / 2.4, it.getY() - 0.04);
        shui.setScale(view.getSize().x / windowWidth, view.getSize().y / windowHeight);
        shui.draw(window);
        break;
    case ElementType::bing:
        bing.setPos(it.getX() + cardWidth / 2.4, it.getY() - 0.04);
        bing.setScale(view.getSize().x / windowWidth, view.getSize().y / windowHeight);
        bing.draw(window);
        break;
    case ElementType::lei:
        lei.setPos(it.getX() + cardWidth / 2.4, it.getY() - 0.04);
        lei.setScale(view.getSize().x / windowWidth, view.getSize().y / windowHeight);
        lei.draw(window);
        break;
    case ElementType::cao:
        cao.setPos(it.getX() + cardWidth / 2.4, it.getY() - 0.04);
        cao.setScale(view.getSize().x / windowWidth, view.getSize().y / windowHeight);
        cao.draw(window);
        break;
    case ElementType::yan:
        yan.setPos(it.getX() + cardWidth / 2.4, it.getY() - 0.04);
        yan.setScale(view.getSize().x / windowWidth, view.getSize().y / windowHeight);
        yan.draw(window);
        break;
    case ElementType::huo:
        huo.setPos(it.getX() + cardWidth / 2.4, it.getY() - 0.04);
        huo.setScale(view.getSize().x / windowWidth, view.getSize().y / windowHeight);
        huo.draw(window);
        break;
    case ElementType::feng:
        feng.setPos(it.getX() + cardWidth / 2.4, it.getY() - 0.04);
        feng.setScale(view.getSize().x / windowWidth, view.getSize().y / windowHeight);
        feng.draw(window);
        break;
    default:
        break;
    }
}
void  Game::GetMemento() 
{
    saves.push_back(Memento(mState, this));
}

void Game::LoadMemento(int index)
{
    if (index < saves.size())
    {
        for (int i = 0; i < saves.size(); i++)
        {
            if (i == index)
            {
                mState = saves[i].save;
                this->characterVector = saves[i].characterVector;	//角色容器，用于存储场上所有的角色
                this->enemyVector= saves[i].enemyVector;	  //怪物容器，用于存储场上所有的怪物
                this->cards= saves[i].cards;
                this->diceNum = saves[i].diceNum;
                this->firstInitDice = saves[i].firstInitDice;
                this->firstConfirm = saves[i].firstConfirm;
                this->playerTurnOver = saves[i].playerTurnOver;
                this->enemyTurnOver = saves[i].enemyTurnOver;
                this->enemyAction = saves[i].enemyAction;
                this->isWin = saves[i].isWin;
                this->initdice = saves[i].initdice;
                this->isPlayerFirst = saves[i].isPlayerFirst;
                break;
            }
            
        }
    }
    else {
        cout << "不存在这么多存档！" << endl;
    }
   

}

Enemy* Game::CurrentEnemy() {
    for (auto it = enemyVector.begin(); it != enemyVector.end(); it++)
    {
        if (it->IsSelected())
        {
            return &(*it);
        }
    }

}
Character* Game::CurrentCharacter() {
    for (auto it = characterVector.begin(); it != characterVector.end(); it++)
    {
        if (it->IsSelected())
        {
            return &(*it);
        }
    }

}

void Game::placeVectorAutoPlace() 
{
    int index = 1;
    for (auto it = 0; it < playerPlaceVector.size(); it++)
    {
        for (auto i = 0; i < playerPlaceVector[it].size(); i++)
        {
            switch (index)
            {
            case 1:
                playerPlaceVector[it][i].setPos(placeCardX1, placeCardY1);
                break;
            case 2:
                playerPlaceVector[it][i].setPos(placeCardX2, placeCardY1);
                break;
            case 3:
                playerPlaceVector[it][i].setPos(placeCardX1, placeCardY2);
                break;
            case 4:
                playerPlaceVector[it][i].setPos(placeCardX2, placeCardY2);
                break;
            }
            index++;
        }
    }
    index = 1;
    for (auto it = 0; it < enemyPlaceVector.size(); it++)
    {
        for (auto i = 0; i < enemyPlaceVector[it].size(); i++)
        {
            switch (index)
            {
            case 1:
                enemyPlaceVector[it][i].setPos(placeCardX1, placeCardY3);
                break;
            case 2:
                enemyPlaceVector[it][i].setPos(placeCardX2, placeCardY3);
                break;
            case 3:
                enemyPlaceVector[it][i].setPos(placeCardX1, placeCardY4);
                break;
            case 4:
                enemyPlaceVector[it][i].setPos(placeCardX2, placeCardY4);
                break;
            }
            index++;
        }
    }
    return;
}

void Game:: summonedVectorAutoPlace()
{
    int index = 1;
    for (auto i = 0; i < playerSummonedVector.size(); i++)
    {
        switch (index)
        {
        case 1:
            playerSummonedVector[i]->setPos(summonedCardX1, summonedCardY1);
            break;
        case 2:
            playerSummonedVector[i]->setPos(summonedCardX2, summonedCardY1);
            break;
        case 3:
            playerSummonedVector[i]->setPos(summonedCardX1, summonedCardY2);
            break;
        case 4:
            playerSummonedVector[i]->setPos(summonedCardX2, summonedCardY2);
            break;
        }
        index++;
    }
    index = 1;
    for (auto i = 0; i < enemySummonedVector.size(); i++)
    {
        switch (index)
        {
        case 1:
            enemySummonedVector[i]->setPos(summonedCardX1, summonedCardY3);
            break;
        case 2:
            enemySummonedVector[i]->setPos(summonedCardX2 , summonedCardY3);
            break;
        case 3:
            enemySummonedVector[i]->setPos(summonedCardX1, summonedCardY4 );
            break;
        case 4:
            enemySummonedVector[i]->setPos(summonedCardX2 , summonedCardY4);
            break;
        }
        index++;
    }
    return;
}


void Game::addPlayerPlace(Place f) 
{
    switch (f.type)
    {
    case PlaceType::投掷:
        playerPlaceVector[0].push_back(f);
        break;
    case PlaceType::换人:
        playerPlaceVector[1].push_back(f);
        break;
    case PlaceType::攻击:
        playerPlaceVector[2].push_back(f);
        break;
    case PlaceType::结束:
        playerPlaceVector[3].push_back(f);
        break;
    default:
        break;
    }
}
void Game::addEnemyPlace(Place f)
{
    switch (f.type)
    {
    case PlaceType::投掷:
       enemyPlaceVector[0].push_back(f);
        break;
    case PlaceType::换人:
        enemyPlaceVector[1].push_back(f);
        break;
    case PlaceType::攻击:
        enemyPlaceVector[2].push_back(f);
        break;
    case PlaceType::结束:
        enemyPlaceVector[3].push_back(f);
        break;
    default:
        break;
    }
}
void Game::drawPlaceVector()
{

    for (auto it = 0; it < playerPlaceVector.size(); it++)
    {
            for (auto i = 0; i < playerPlaceVector[it].size(); i++)
            {
                playerPlaceVector[it][i].draw(window);
            }
    }

    for (auto it = 0; it < enemyPlaceVector.size(); it++)
    {
        for (auto i = 0; i < enemyPlaceVector[it].size(); i++)
        {
            enemyPlaceVector[it][i].draw(window);
        }
    }
    return;
}
void Game::drawSummonedVector()
{
    for (auto i = 0; i < enemySummonedVector.size(); i++)
    {
        enemySummonedVector[i]->draw(window);
    }
     
    for (auto i = 0; i < playerSummonedVector.size(); i++)
    {
        playerSummonedVector[i]->draw(window);
    }
    return;
}

void Game::resetPlaceCardTimes()
{
    for (auto it = 0; it < playerPlaceVector.size(); it++)
    {
        for (auto i = 0; i < playerPlaceVector[it].size(); i++)
        {
            playerPlaceVector[it][i].times=1;
        }
    }

    for (auto it = 0; it < enemyPlaceVector.size(); it++)
    {
        for (auto i = 0; i < enemyPlaceVector[it].size(); i++)
        {
            playerPlaceVector[it][i].times = 1;
        }
    }
}

void Game::drawAbilityBanner(Ability* a)
{
    string name = CurrentCharacter()->name;
    int index = 0;
    for (auto i = sAbility.begin(); i != sAbility.end(); i++)
    {
        if ((*i) == a)
        {
            break;
        }
        index++;
    }
    if (name == "xingqiu") 
    {
        abilityBanner[index].setScale(view.getSize().x / windowWidth, view.getSize().y / windowHeight);
        abilityBanner[index].draw(window);
    }
    else if (name == "keqing")
    {
        abilityBanner[index+3].setScale(view.getSize().x / windowWidth, view.getSize().y / windowHeight);
        abilityBanner[index+3].draw(window);
    }
    else if (name == "kaya")
    {
        abilityBanner[index+6].setScale(view.getSize().x / windowWidth, view.getSize().y / windowHeight);
        abilityBanner[index+6].draw(window);
    }
}