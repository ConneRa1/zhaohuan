#include "PlayerTurnState.h"
PlayerTurnState::PlayerTurnState(Game* game) :State(game){

}

void PlayerTurnState::HandleCard(Card* c) {         //卡牌生效
    //食物的加buff示例
    /*a1.addBuff(Buff(1, BuffType::盾, 2, 36, 36, texarr[110]));
    a1.addBuff(Buff(1, BuffType::加攻, 2, 36, 36, texarr[111]));
    a1.addBuff(Buff(1, BuffType::饱, 1, 36, 36, texarr[112]));*/
    //添加场景卡的示例
    //addPlayerPlace(Place(PlaceType::回合, ConcreateCard::凯瑟琳,1, 1, windowWidth*placeCardWidth, windowHeight*placeCardHeight, texarr[350]));
    //addEnemyPlace(Place(PlaceType::回合, ConcreateCard::西风大教堂, 1, 1, windowWidth * placeCardWidth, windowHeight * placeCardHeight, texarr[350]));
    int num = 0;
    Character* role = (Character*)target;
    if (role == NULL)role = mGame->CurrentCharacter();
    switch (c->name)
    {
    //event
    case ConcreateCard::最好的伙伴: {
        /*int n = 0;
        for (int i = 0; i < 2; i++) {
            mGame->diceNum.m[ElementType::cai]++;
        }
        vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
        sort(vec.begin(), vec.end(), Cost::cmp);
        for (int i = 0; i < mGame->diceNum.m[ElementType::cai]; i++) {
            mGame->dices[n].sprite.setTexture(mGame->texarr[200]);
            n++;
        }
        for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
        {
            if (it->first != ElementType::cai) {
                for (int i = 0; i < it->second; i++) {
                    mGame->dices[n].sprite.setTexture(mGame->texarr[200 + (int)it->first]);
                    n++;
                }
            }
        }*/
        break;
    }
    case ConcreateCard::交给我吧:
        quickChange = true;
        break; 
    case ConcreateCard::白垩之术:
        for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
        {
            if (it->getNp() >= 1 && &(*it)!=mGame->CurrentCharacter())
            {
                it->setNp(it->getNp() - 1);
                num++;
            }
            mGame->CurrentCharacter()->setNp(mGame->CurrentCharacter()->getNp() + num);
        }
        break;
    case ConcreateCard::莫娜:
        mGame->CurrentCharacter()->setNp(mGame->CurrentCharacter()->getNp() + 1);
        break;
    case ConcreateCard::鹤归:
        break;
    case ConcreateCard::罗莎莉亚:
        luoshayiya = true;
        break;
    case ConcreateCard::无中生有:
        mGame->cards.drawCard();
        mGame->cards.drawCard();
        mGame->cards.autoPlace();
        break;
    //food
    case ConcreateCard::仙跳墙:
        if (!role->isBao())
        {
            target->addBuff(Buff(1, BuffType::饱, 1, 36, 36, mGame->texarr[112]));
            target->addBuff(Buff(1, BuffType::大招, 1, 36, 36, mGame->texarr[111]));
        }
        
        //target->addBuff()
        break;
    case ConcreateCard::土豆饼:
        if (!role->isBao())
        {
            target->addBuff(Buff(1, BuffType::饱, 1, 36, 36, mGame->texarr[112]));
            target->addHp(2);
            healtarget = target;
            healtimer = 200;
            healNum = 2;
        }
        break;
    case ConcreateCard::烧鸡:
        if (!role->isBao())
        {
            target->addBuff(Buff(1, BuffType::饱, 1, 36, 36, mGame->texarr[112]));
            target->addHp(1);
            healtarget = target;
            healtimer = 200;
            healNum = 1;
        }
        break;
    case ConcreateCard::莲花酥:
        if (!role->isBao())
        {
            target->addBuff(Buff(1, BuffType::饱, 1, 36, 36, mGame->texarr[112]));
            target->addBuff(Buff(1, BuffType::盾, 3, 36, 36, mGame->texarr[110]));
        }
        break;
    //场地
       /* addPlayerPlace(Place(PlaceType::换人, ConcreateCard::刘苏, 1, 1, windowWidth * placeCardWidth, windowHeight * placeCardHeight, texarr[350]));
        addPlayerPlace(Place(PlaceType::结束, ConcreateCard::璃月港口, 1, 2, windowWidth * placeCardWidth, windowHeight * placeCardHeight, texarr[350]));
        addPlayerPlace(Place(PlaceType::结束, ConcreateCard::望舒客栈, 1, 2, windowWidth * placeCardWidth, windowHeight * placeCardHeight, texarr[350]));
        addPlayerPlace(Place(PlaceType::结束, ConcreateCard::西风大教堂, 1, 2, windowWidth * placeCardWidth, windowHeight * placeCardHeight, texarr[350]));*/
    case ConcreateCard::凯瑟琳:
        mGame->addPlayerPlace(Place(PlaceType::换人, ConcreateCard::凯瑟琳, 1, 1, windowWidth * placeCardWidth, windowHeight * placeCardHeight, mGame->texarr[350]));
        break;
    case ConcreateCard::刘苏:
        mGame->addPlayerPlace(Place(PlaceType::换人, ConcreateCard::刘苏, 1, 1, windowWidth * placeCardWidth, windowHeight * placeCardHeight, mGame->texarr[350]));
        break;
    case ConcreateCard::璃月港口:
        mGame->addPlayerPlace(Place(PlaceType::结束, ConcreateCard::璃月港口, 1, 2, windowWidth * placeCardWidth, windowHeight * placeCardHeight, mGame->texarr[350]));
        break;
    case ConcreateCard::望舒客栈:
        mGame->addPlayerPlace(Place(PlaceType::结束, ConcreateCard::望舒客栈, 1, 2, windowWidth * placeCardWidth, windowHeight * placeCardHeight, mGame->texarr[350]));
         break;
    case ConcreateCard::西风大教堂:
        mGame->addPlayerPlace(Place(PlaceType::结束 , ConcreateCard::西风大教堂, 1, 2, windowWidth * placeCardWidth, windowHeight * placeCardHeight, mGame->texarr[350]));
        break;
    case ConcreateCard::常九爷:
        mGame->addPlayerPlace(Place(PlaceType::攻击, ConcreateCard::常九爷, 1, 3, windowWidth * placeCardWidth, windowHeight * placeCardHeight, mGame->texarr[350]));
        break;
    case ConcreateCard::晨曦酒庄:
        mGame->addPlayerPlace(Place(PlaceType::换人, ConcreateCard::晨曦酒庄, 1, 1, windowWidth * placeCardWidth, windowHeight * placeCardHeight, mGame->texarr[350]));
        break;
    case ConcreateCard::参量质变仪:
        mGame->addPlayerPlace(Place(PlaceType::攻击, ConcreateCard::参量质变仪, 1, 3, windowWidth * placeCardWidth, windowHeight * placeCardHeight, mGame->texarr[350]));
        break;
    case ConcreateCard::骑士团图书馆:
        mGame->addPlayerPlace(Place(PlaceType::投掷, ConcreateCard::骑士团图书馆, 1, 1, windowWidth * placeCardWidth, windowHeight * placeCardHeight, mGame->texarr[350]));

        break;

    //装备
    case ConcreateCard::旅行剑:
        target->addEquipment(Buff(999,BuffType::武器,1,100,100,mGame->texarr[112]));
        break;
    case ConcreateCard::白铁大剑:
        target->addEquipment(Buff(999, BuffType::武器, 1, 100, 100, mGame->texarr[112]));
        break;
    //圣遗物
    /*case ConcreateCard::不动玄石之相:
        break;*/

    case ConcreateCard::唤雷的头冠:
        target->addRelic(Buff(999, BuffType::圣遗物, 1, 100, 100, mGame->texarr[112]));
        break;
    case ConcreateCard::破冰踏雪的回音:
        target->addRelic(Buff(999, BuffType::圣遗物, 1, 100, 100, mGame->texarr[112]));
        break;
    case ConcreateCard::酒渍船帽:
        target->addRelic(Buff(999, BuffType::圣遗物, 1, 100, 100, mGame->texarr[112]));
        break;
    }
}
void PlayerTurnState::HandleDazhao(vector<Buff>& dazhao)
{
    if (isChanged)
    {
        for (auto it = dazhao.begin(); it != dazhao.end(); it++)
        {
            if ((*it).name == "kaiya"&& it->times>0)
            {
                mGame->CurrentEnemy()->getHurt(2);
                showHurt = true;
                HandleReact(ElementType::bing, false);
                it->times -= 1;
            }
        }
    }
    else if (hurtOver)
    {
        for (auto it = dazhao.begin(); it != dazhao.end(); it++)
        {
            if ((*it).name == "xingqiu" && it->times > 0 && !xingqiu &&triggeredAbility==mGame->sAbility[0])
            {
                cout << "行秋" << endl;
                mGame->CurrentEnemy()->getHurt(1);
                it->times -= 1;
                xingqiu = true;
                HandleReact(ElementType::shui, false);
                xingqiu = false;
            }
        }
    }
}
void PlayerTurnState::HandleReact(ElementType e,bool over)
{
    target = mGame->CurrentEnemy();
    if (target->checkReact(e))     //有反应进反应
    {
        cout << "有元素反应" << endl;
        reactHurtOver = over;
        showReact = true;
        reactType = target->doReact(e);
        doReact(reactType, true);
        if (target->gethp() <= 0)
        {
            target->Die();
            target->Selected(false, false);
            for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++)
            {
                if ((*it).gethp() > 0)
                {
                    (*it).Selected(true, false);
                    break;
                }
            }
        }
        int index = 0; bool flag = false;
        for (auto it = 0; it < mGame->playerPlaceVector[2].size(); it++)
        {
            if (mGame->playerPlaceVector[2][it].name == ConcreateCard::常九爷)
            {
                if (mGame->playerPlaceVector[2][it].num < 3 && reactType == ReactType::超导)
                {
                    mGame->playerPlaceVector[2][it].num++;
                }
                if (mGame->playerPlaceVector[2][it].num == 3)
                {
                    flag = true; index = it;
                    mGame->cards.drawCard();
                    mGame->cards.drawCard();
                    mGame->cards.autoPlace();
                }
            }
        }
        if (flag)
        {
            mGame->playerPlaceVector[2].erase((mGame->playerPlaceVector[2].begin() + index));
        }
        
    }
    else {
        if (target->gethp() <= 0)
        {
            target->Die();
            target->Selected(false, false);
            for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++)
            {
                if ((*it).gethp() > 0)
                {
                    (*it).Selected(true, false);
                    break;
                }
            }
        }
        if (mGame->isWin) {
            mGame->ChangeState(new GameEndState(mGame));
        }
        else {
            vector<int> index;
            int id = 0;
            for (auto it = mGame->playerPlaceVector[2].begin(); it != mGame->playerPlaceVector[2].end(); it++)
            {
                if ((*it).name == ConcreateCard::常九爷 && (*triggeredAbility).getElement() == ElementType::cai)
                {
                    if ((*it).num < 3)
                    {
                        (*it).num++;
                    }
                    if ((*it).num == 3)
                    {
                        index.push_back(id);
                        mGame->cards.drawCard();
                        mGame->cards.drawCard();
                        mGame->cards.autoPlace();
                    }
                }
                else if ((*it).name == ConcreateCard::参量质变仪)
                {
                    if ((*it).num < 3 && (*triggeredAbility).getElement() != ElementType::cai)
                    {
                        (*it).num++;
                    }
                    if ((*it).num == 3)
                    {
                        index.push_back(id);
                        for (int i = 0; i < 3; i++) {
                            random_device rd;
                            mGame->diceNum.m[ElementType(rd() % (int)ElementType::count)]++;
                        }
                    }
                }
                id++;
            }
            
            for (int i = 0; i < index.size(); i++)
            {
                mGame->playerPlaceVector[2].erase((mGame->playerPlaceVector[2].begin() + index[i]));
            }
            if (over)
            {
                if (!mGame->enemyTurnOver)
                {
                    mGame->ChangeState(new EnemyTurnState(mGame));
                }
                else {
                    mGame->ChangeState(new TurnEndState(mGame));
                }
            }
            
        }
    }
}
void PlayerTurnState::HandleChangeRole(Character* c)
{
    currentRole = mGame->CurrentCharacter();
    c->dazhao = currentRole->dazhao;
    currentRole->dazhao.clear();
    c->Selected(true, true);
    HandleDazhao(c->dazhao);
    if (c->name == "xingqiu")
    {
        for (auto i = 0; i < 3; i++)
        {
            mGame->sAbility[i] = mGame->abilityVector[i];
        }
    }
    else if (c->name == "keqing")
    {
        for (auto i = 0; i < 3; i++)
        {

            mGame->sAbility[i] = mGame->abilityVector[i + 3];
        }
    }
    else if (c->name == "kaiya")
    {
        for (auto i = 0; i < 3; i++)
        {

            mGame->sAbility[i] = mGame->abilityVector[i + 6];
        }
    }
    for (auto i = mGame->characterVector.begin(); i != mGame->characterVector.end(); i++)
    {
        if (&(*i) != c)
        {
            i->Selected(false, true);
        }
    }

    for (auto it = mGame->playerPlaceVector[1].begin(); it != mGame->playerPlaceVector[1].end(); it++)
    {
        if ((*it).name == ConcreateCard::刘苏)
        {
            if ((*it).times > 0)
            {
                if (target->getNp() == 0)
                {
                    target->setNp(target->getNp() + 1);
                }
            }
            (*it).times = 0;
        }
    }
    target = NULL;
}
void PlayerTurnState::doReact(ReactType r, bool toEnemy)
{
    switch (r)
    {
    case ReactType::蒸发:
        target->getHurt(2);
        break;
    case ReactType::感电:
        if (toEnemy)
        {
            for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++)
            {
                if (&(*it) != mGame->CurrentEnemy()&&(*it).gethp()>0)
                {
                    it->getHurt(1);	//后面改一下，只扣后台的
                    if (it->gethp() <= 0)
                    {
                        it->Die();
                    }
                }
                
            }
        }
        else {
            for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
            {
                if (&(*it) != mGame->CurrentCharacter() && (*it).gethp() > 0)
                {
                    it->getHurt(1);	//后面改一下，只扣后台的
                    if (it->gethp() <= 0)
                    {
                        it->Die();
                    }
                }
            }
        }
        break;
    case ReactType::冻结:
        target->setfrozen(true);
        cout << "冻结!" << endl;
        break;
    case ReactType::超导:
        cout << "超导" << endl;
        if (toEnemy)
        {
            for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++)
            {
                if (&(*it) != mGame->CurrentEnemy() && (*it).gethp() > 0)
                {
                    it->getHurt(1);	//后面改一下，只扣后台的
                    if (it->gethp() <= 0)
                    {
                        it->Die();
                    }
                }

            }
        }
        else {
            for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
            {
                if (&(*it) != mGame->CurrentCharacter() && (*it).gethp() > 0)
                {
                    it->getHurt(1);	//后面改一下，只扣后台的
                    if (it->gethp() <= 0)
                    {
                        it->Die();
                    }
                }
            }
        }
        break;
    default:
        break;
    }


}
void PlayerTurnState::Input() {
    if (bannertime >= bannerTime)
    {
        Event event;
        while (mGame->window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                mGame->window.close();
                mGame->gameOver = false;
                mGame->gameQuit = true;
            }
            if (event.type == Event::EventType::KeyReleased && event.key.code == Keyboard::Escape)
            {
                mGame->window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::F11) {
                mGame->toggleFullscreen();
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                LeftButtonDown(Mouse::getPosition(mGame->window));
            }
            if (event.type == sf::Event::MouseMoved)
            {
                if (isCardTriggered)
                {
                    if (diceTriggeredNum >= triggeredCard->cost)
                    {
                        isDragging = true;
                    }
                    if (isDragging)
                    {
                        dragOffset = Vector2f(triggeredCard->getScalex()*windowWidth/20, triggeredCard->getScaley() * windowHeight / 4);
                        cout << dragOffset.x << endl;
                        Vector2i mousePos = Mouse::getPosition(mGame->window);
                        Vector2f pos = static_cast<Vector2f>(mousePos) - dragOffset;
                        triggeredCard->setPos(pos.x / mGame->view.getSize().x, pos.y / mGame->view.getSize().y);
                    }
                }
                
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
            {
                if (isCardTriggered&& diceTriggeredNum >= triggeredCard->cost)
                {
                    if (triggeredCard->getPosY() < heldCardY - moveOffset * 2)
                    {
                        selectedDiceNum = 0;
                        mGame->diceNum = mGame->diceNum - diceTriggeredNum;
                        isCardFinished = true;
                        isCardTriggered = false;
                        isConsumingDice = false;
                        diceTriggeredNum = Cost();
                        for (int i = 0; i < mGame->diceNum.getSize(); i++)
                        {
                            diceTriggered[i] = false;
                        }
                        for (int i = mGame->diceNum.getSize(); i < 8; i++)
                        {
                            diceTriggered[i] = true;
                        }
                    }
                    else {
                        CancelConsumingDice(Mouse::getPosition(mGame->window));
                    }
                    isDragging = false;
                }
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::S)
            {
                cout << "存档!" << endl;
                mGame->GetMemento();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num1)
            {
                mGame->LoadMemento(0);
                cout << "读档1" << endl;
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num2)
            {
                mGame->LoadMemento(1);
                cout << "读档2" << endl;
            }
            /* if (event.type == Event::EventType::KeyReleased && event.key.code == Keyboard::Add)
             {
                 soundVolume += 5;
                 bkMusic.setVolume(soundVolume);
             }
             if (event.type == Event::EventType::KeyReleased && event.key.code == Keyboard::Subtract)
             {
                 soundVolume -= 5;
                 bkMusic.setVolume(soundVolume);
             }
             if (event.type == Event::EventType::KeyPressed && event.key.code == Keyboard::Multiply || event.key.code == Keyboard::Enter)
             {
                 if (MusicOn)
                 {
                     bkMusic.stop();
                 }
                 else {
                     bkMusic.play();
                 }
                 MusicOn = !MusicOn;
             }*/
        }
    }
    
}
void PlayerTurnState::Logic() {
    if (bannertime < bannerTime)bannertime++;
    if (bannertime >= bannerTime)
    {
        if (!flag)
        {
            mGame->cards.setHeldCardsPosition(0.5 - mGame->cards.getCardNum() * cardWidth / 4, heldCardY, cardWidth * 0.52);
            flag = true;
            placedDice.clear();
            //每次进入这个状态，都重置骰子的位子
            int num = 0;
            /*for (auto i = mGame->diceNum.m.begin(); i != mGame->diceNum.m.end(); i++) {
                cout << (*i).first << " " << (*i).second << endl;
            }*/
            for (int i = 0; i < mGame->diceNum.getSize(); i++)
            {
                placedDice.push_back(mGame->chooseDice);
                if (num % 2 == 0)
                {
                    num = 0;
                }
                placedDice[i].setPos(num * consumeDiceOffsetX + consumeDiceX, consumeDiceY + (i / 2) * consumeDiceOffsetY);
                num++;
            }
            for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++) {
                if (it->IsSelected())
                {
                    currentRole = &(*it);
                    break;
                }
            }
        }
    }
    if (mGame->firstConfirm)
    {
        if (times++ >= 500)
        {
            cout << "玩家回合结束" ;
            mGame->playerTurnOver = true;
            mGame->firstConfirm = false;
            if (!mGame->enemyTurnOver)
            {
                mGame->isPlayerFirst = true;
                cout << "，进入enemy回合" << endl;
                mGame->ChangeState( new EnemyTurnState(mGame));
            }
            else
            {
                mGame->isPlayerFirst = false;
                cout << "，进入下一回合" << endl;
                mGame->ChangeState(new TurnEndState(mGame));
            }
        }
    }
    else if (hurtOver)
    {
        if (hurtTimer >= hurtTime*0.75)
        {
            //hurtTimer = 0;
            HandleDazhao(mGame->CurrentCharacter()->dazhao);
            HandleReact(triggeredAbility->getElement(),true);
            hurtOver = false;

        }
    }
    else if (reactHurtOver)
    {
        if (delayTimer > hurtTime / 2)//延时进行反应
        {
            if (reactHurtTimer >= hurtTime)
            {
                reactHurtTimer = 0;
                if (mGame->isWin) {
                    mGame->ChangeState(new GameEndState(mGame));
                }
                else {
                    if (!mGame->enemyTurnOver)
                    {
                        mGame->ChangeState(new EnemyTurnState(mGame));
                    }
                    else {
                        mGame->ChangeState(new TurnEndState(mGame));

                    }
                }
            }
        }
    }
    else if (isActed)
    {
        if (triggeredAbility != NULL && target != NULL)
        {
            if (triggeredAbility != *(mGame->sAbility.end() - 1))
            {
                currentRole->setNp(currentRole->getNp() + 1);
            }
            else {
                currentRole->setNp(0);
                //大招效果
                string name = mGame->CurrentCharacter()->name;
                if (name == "xingqiu")
                {
                    mGame->CurrentCharacter()->dazhao.push_back(Buff(2, BuffType::大招, 1, 36, 36,"xingqiu" ,mGame->texarr[120]));
                }
                else if (name == "kaiya")
                {
                    mGame->CurrentCharacter()->dazhao.push_back(Buff(2, BuffType::大招, 2, 36, 36,"kaiya" ,mGame->texarr[121]));
                }
                else if (name == "keqing")
                {
                    for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++)
                    {
                        if (&(*it)!=mGame->CurrentEnemy())
                        {
                            it->getHurt(3);
                        }
                    }
                }
            }
            cout << "玩家回合结束，进入enemy回合" << endl;
            //融入元素反应
            //先判断能否反应，不能：直接减、挂元素，能：元素反应，给出reacthurt,先正常伤害，再接上反应伤害
            target = mGame->CurrentEnemy(); 
            target->getHurt(currentRole,(*triggeredAbility).getDamage(),triggeredAbility==*(mGame->sAbility.end()-1));
            int flag = 0;
            for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++)
            {
                if ((*it).gethp() > 0)
                {
                    break;
                }
                flag += 1;
            }
            if (flag == mGame->enemyNum)
            {
                //进入胜利界面
                mGame->isWin = true;
                mGame->ChangeState(new GameEndState(mGame));
            }
            /*else {
                mGame->ChangeState( new EnemyTurnState(mGame));
            }*/
            isActed = false;
        }
        hurtOver = true;
        showHurt = true;
    }
    else if (isCardFinished)
    {
        //使用当前卡片
        isCardFinished = false;
        isCardTriggered = false;
        isConsumingDice = false;

        HandleCard(triggeredCard);
        mGame->cards.useCard(triggeredCard);
        mGame->cards.autoPlace();
        triggeredCard = NULL;
    }
    else if (isChanged)
    {
        if (times == 0)
        {
            Character* c = (Character*) target;
            currentRole = mGame->CurrentCharacter();            
            //HandleDazhao(currentRole->dazhao);
            c->dazhao = currentRole->dazhao;
            currentRole->dazhao.clear();
            c->Selected(true,true);
            HandleDazhao(c->dazhao);
            if (c->name == "xingqiu")
            {
                for (auto i = 0; i<3; i++)
                {
                    mGame->sAbility[i] = mGame->abilityVector[i];
                }
            }
            else if (c->name == "keqing")
            {
                for (auto i = 0; i < 3; i++)
                {

                    mGame->sAbility[i] = mGame->abilityVector[i+3];
                }
            }
            else if (c->name == "kaiya")
            {
                for (auto i = 0; i < 3; i++)
                {

                    mGame->sAbility[i] = mGame->abilityVector[i+6];
                }
            }
            for (auto i = mGame->characterVector.begin(); i != mGame->characterVector.end(); i++)
            {
                if (&(*i) != c)
                {
                    i->Selected(false,true);
                }
            }
            
            for (auto it = mGame->playerPlaceVector[1].begin(); it != mGame->playerPlaceVector[1].end(); it++)
            {
                if ((*it).name == ConcreateCard::刘苏)
                {
                    if ((*it).times > 0)
                    {
                        if (target->getNp() == 0)
                        {
                            target->setNp(target->getNp() + 1);
                        }
                    }
                    (*it).times = 0;
                }
            }
            target = NULL;
            isChangingRole = false;
        }
        
        if (quickChange)
        {
            isChanged = false;
        }
        else {
            if (times++ >= 500)
            {
                cout << "换人消耗回合";
                if (!mGame->enemyTurnOver)
                {
                    cout << "，进入enemy回合" << endl;
                    mGame->ChangeState(new EnemyTurnState(mGame));
                }
                else
                {
                    cout << "，进入下一回合" << endl;
                    mGame->ChangeState(new PlayerTurnState(mGame));
                }

            }
        }
    }
}
void PlayerTurnState::Draw() {
    mGame->window.clear();//清屏
    mGame->view.setSize(sf::Vector2f(mGame->window.getSize()));
    mGame->view.setCenter(sf::Vector2f(mGame->window.getSize()) / 2.f);
    mGame->window.setView(mGame->view);

    mGame->backGround.sprite.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
    mGame->backGround.draw(mGame->window);

    for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++) {
        mGame->showElement(*it);
        it->draw(mGame->window, mGame->view.getSize().x / windowWidth * it->getScalex(), mGame->view.getSize().y / windowHeight * it->getScaley(), mGame->shader);
    }
    for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++) {
        mGame->showElement(*it);
        it->draw(mGame->window, mGame->view.getSize().x / windowWidth * it->getScalex(), mGame->view.getSize().y / windowHeight * it->getScaley(), mGame->shader);
    }

    mGame->placeVectorAutoPlace();
    mGame->drawPlaceVector();

    if (isConsumingDice)
    {
        mGame->dicebg.setScale(mGame->view.getSize().x / windowWidth * (float)windowWidth * diceBgWidth / (float)mGame->dicebg.sprite.getTexture()->getSize().x,
            mGame->view.getSize().y / windowHeight * (float)windowHeight * diceBgHeight / (float)mGame->dicebg.sprite.getTexture()->getSize().y);
        mGame->dicebg.draw(mGame->window);
        for (int i = 0; i < selectedDiceNum; i++)
        {
            mGame->diceTriggerred[i].setScale(mGame->view.getSize().x / windowWidth * mGame->diceTriggerred[i].getScalex(), mGame->view.getSize().y / windowHeight * mGame->diceTriggerred[i].getScaley());
            mGame->diceTriggerred[i].draw(mGame->window);
        }
        int n = 0;
        vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
        sort(vec.begin(), vec.end(), Cost::cmp);
        for (int i = 0; i < mGame->diceNum.m[ElementType::cai]; i++) {
            placedDice[n].sprite.setTexture(mGame->texarr[200]);
            placedDice[n].setScale(mGame->view.getSize().x / windowWidth * placedDice[n].getScalex(), mGame->view.getSize().y / windowHeight * placedDice[n].getScaley());
            placedDice[n].draw(mGame->window);
            n++;
        }
        for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
        {
            if (it->first != ElementType::cai) {
                for (int i = 0; i < it->second; i++) {
                    placedDice[n].sprite.setTexture(mGame->texarr[200 + (int)it->first]);
                    placedDice[n].setScale(mGame->view.getSize().x / windowWidth * placedDice[n].getScalex(), mGame->view.getSize().y / windowHeight * placedDice[n].getScaley());
                    placedDice[n].draw(mGame->window);
                    n++;
                }
            }
        }
        if (isAbilityTriggered)
        {
            mGame->drawAbilityBanner(triggeredAbility);
            mGame->target.setPos((*target).getX(), (*target).getY());
            mGame->target.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->target.draw(mGame->window);
            mGame->chupai.setScale(mGame->view.getSize().x / windowWidth * (float)windowWidth * confirmButtonWidth / (float)mGame->confirmButton.sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * confirmButtonHeight / (float)mGame->confirmButton.sprite.getTexture()->getSize().y);
            mGame->chupai.draw(mGame->window);
        }
        else if (isCardTriggered)
        {
            //mGame->cards.setHeldCardsPositionY();
            mGame->cards.draw(mGame->window, mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
        }
        else if (isChangingRole)
        {
            mGame->changeConfirm.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->changeConfirm.draw(mGame->window);
            mGame->changeTarget.setPos((*target).getX(), (*target).getY());
            mGame->changeTarget.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->changeTarget.draw(mGame->window);
        }
    }
    else {
        mGame->cards.draw(mGame->window, mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
        for (auto it = mGame->ui.begin(); it != mGame->ui.end(); it++) {
            it->sprite.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            it->draw(mGame->window);
        }
        int n = 0;
        vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
        sort(vec.begin(), vec.end(), Cost::cmp);
        for (int i = 0; i < mGame->diceNum.m[ElementType::cai]; i++) {
            mGame->dices[n].sprite.setTexture(mGame->texarr[200]);
            n++;
        }
        for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
        {
            if (it->first != ElementType::cai) {
                for (int i = 0; i < it->second; i++) {
                    mGame->dices[n].sprite.setTexture(mGame->texarr[200 + (int)it->first]);
                    n++;
                }
            }
        }
        for (int i = 0; i < mGame->diceNum.getSize(); i++)
        {
            mGame->dices[i].setScale(mGame->view.getSize().x / windowWidth * mGame->dices[i].getScalex(), mGame->view.getSize().y / windowHeight * mGame->dices[i].getScaley());
            mGame->dices[i].draw(mGame->window);
        }

        if (bannertime < bannerTime)
        {
            mGame->cards.setHeldCardsPosition(0.5 - mGame->cards.getCardNum() * cardWidth / 4, heldCardY, cardWidth * 0.52);
            mGame->playerbanner.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->playerbanner.draw(mGame->window);
        }
        else {
            
                for (auto it = mGame->sAbility.begin(); it != mGame->sAbility.end(); it++) {
                    (*it)->Object::setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
                    (*it)->Object::draw(mGame->window);
                }
        }
    }
    if (showHurt)
    {
        int static damage;
        if (hurtTimer == 0)
        {
            target = mGame->CurrentEnemy();
            damage= isChanged?2:target->getHurtNum();
            mGame->hurt.setPos((*target).getX() - 0.01, (*target).getY());
            
        }
        if (hurtTimer++ < hurtTime * 0.75)
        {
            mGame->hurt.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->hurt.draw(mGame->window);

            Text text;
            text.setFont(font);
            text.setString('-'+to_string(damage));
            text.setPosition(mGame->window.getSize().x* ((*target).getX()-hpLeftOffset*0), mGame->window.getSize().y* ((*target).getY() - hpLeftOffset *4.8));
            text.setFillColor(Color::White);
            text.setCharacterSize(float(mGame->window.getSize().y) / float(windowHeight) * fontSize * 4.5);
            mGame->window.draw(text);
        }
        else {
            //hurtTimer = 0;
            showHurt = false;
            //showReact = true;
        }
    }
    else if (showReact)
    {
        if (delayTimer++ > hurtTime / 2)
        {
            if (reactHurtTimer++ < hurtTime)
            {
                Text text;
                Text textReact;
                text.setFont(font);
                text.setCharacterSize(float(mGame->window.getSize().y) / float(windowHeight) * fontSize * 4.5);
                textReact.setFont(font);
                textReact.setCharacterSize(float(mGame->window.getSize().y) / float(windowHeight) * fontSize);
                switch (reactType)
                {
                case ReactType::蒸发:
                    mGame->hurt.setPos((*target).getX() - 0.01, (*target).getY());
                    mGame->hurt.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
                    mGame->hurt.draw(mGame->window);

                    text.setString('-'+to_string(2));
                    text.setFillColor(Color::Blue);
                    text.setPosition(mGame->window.getSize().x* ((*target).getX() - hpLeftOffset * 0), mGame->window.getSize().y* ((*target).getY() - hpLeftOffset * 4.8));
                    mGame->window.draw(text);

                    textReact.setString("Vaporize");
                    textReact.setFillColor(Color::Blue);
                    textReact.setPosition(mGame->window.getSize().x* ((*target).getX() - hpLeftOffset * 0.1), mGame->window.getSize().y* ((*target).getY() + hpLeftOffset * 4));
                    mGame->window.draw(textReact);
                    break;
                case ReactType::感电:
                    text.setString('-' + to_string(1));
                    text.setFillColor(Color(128, 0, 128));

                    textReact.setString("Electro-Charged");
                    textReact.setFillColor(Color(128, 0, 128));
                    for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++)        //后续改一下，只扣后台
                    {
                        if (&(*it) != mGame->CurrentEnemy())
                        {
                            mGame->hurt.setPos(it->getX() - 0.01, it->getY());
                            mGame->hurt.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
                            mGame->hurt.draw(mGame->window);
                            text.setPosition(mGame->window.getSize().x* (it->getX() - hpLeftOffset * 0), mGame->window.getSize().y* (it->getY() - hpLeftOffset * 4.8));
                            mGame->window.draw(text);

                            textReact.setPosition(mGame->window.getSize().x* ((*target).getX() + hpLeftOffset * 0.1), mGame->window.getSize().y* ((*target).getY() + hpLeftOffset * 4));
                            mGame->window.draw(textReact);
                        }
                        
                    }
                    break;
                case ReactType::超导:
                    text.setString('-' + to_string(1));
                    text.setFillColor(Color::White);

                    textReact.setString("Superconduct");
                    textReact.setFillColor(Color::White);
                    for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++)        //后续改一下，只扣后台
                    {
                        if (&(*it) != mGame->CurrentEnemy())
                        {
                            mGame->hurt.setPos(it->getX() - 0.01, it->getY());
                            mGame->hurt.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
                            mGame->hurt.draw(mGame->window);
                            text.setPosition(mGame->window.getSize().x * (it->getX() - hpLeftOffset * 0), mGame->window.getSize().y * (it->getY() - hpLeftOffset * 4.8));
                            mGame->window.draw(text);

                            textReact.setPosition(mGame->window.getSize().x * ((*target).getX() - hpLeftOffset * 0.1), mGame->window.getSize().y * ((*target).getY() + hpLeftOffset * 4));
                            mGame->window.draw(textReact);
                        }
                    }
                    break;
                case ReactType::冻结:
                    
                    textReact.setString("Frozen");
                    textReact.setFillColor(Color(86,193,254));
                    textReact.setPosition(mGame->window.getSize().x * ((*target).getX() - hpLeftOffset *1), mGame->window.getSize().y * ((*target).getY() + hpLeftOffset * 4));
                    mGame->window.draw(textReact);
                    break;
                default:
                    break;
                }
            }
            else {
                target = NULL;
                //reactHurtTimer = 0;
                showReact = false;
            }
        }
    }
    if (healtimer-- > 0)
    {
        if (healNum == 2)
        {
            mGame->heal2.setPos(healtarget->getPosX(), healtarget->getPosY());
            mGame->heal2.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->heal2.draw(mGame->window);

        }
        else {
            mGame->heal1.setPos(healtarget->getPosX(), healtarget->getPosY());
            mGame->heal1.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->heal1.draw(mGame->window);
        }
    }
    mGame->window.display();
}

void PlayerTurnState::CancelConsumingDice(Vector2i mPoint)
{
    if (!mGame->dicebg.isIn(mPoint.x, mPoint.y))
    {
        selectedDiceNum = 0;
        isConsumingDice = false;
        isAbilityTriggered = false;
        isCardTriggered = false;
        isChangingRole = false;
        target = NULL;
        diceTriggeredNum = Cost();
        mGame->cards.autoPlace();
        for (int i = 0; i < mGame->diceNum.getSize(); i++)
        {
            diceTriggered[i] = false;
        }
    }
}
bool PlayerTurnState::CheckChupai(Vector2i mPoint)
{
    if (mGame->chupai.isIn(mPoint.x, mPoint.y))
    {
        return true;
    }
    return false;
}
void PlayerTurnState::LeftButtonDown(Vector2i mPoint)   //什么时候要消耗骰子，！isCardTriggered 点击卡片，点击角色，！isAbilityTriggered 点击技能
{
    if (isConsumingDice)
    {
        if (isAbilityTriggered)
        {
            Cost cost = triggeredAbility->cost;
            if (currentRole->haveRelic()) {
                if (cost.m[currentRole->getElement()] > 0)
                    cost.m[currentRole->getElement()]--;
                else {
                    cost.m[ElementType::cai]--;
                }
            }
                

            if (diceTriggeredNum >= cost)
            {
                cout << "yes" << endl;
                if (CheckChupai(mPoint))
                {
                    selectedDiceNum = 0;
                    target = mGame->CurrentEnemy(); //这里target点击确认会变成自己，先这么改
                    mGame->diceNum = mGame->diceNum - diceTriggeredNum;
                    isActed = true;
                    isConsumingDice = false;
                    diceTriggeredNum = Cost();
                    for (int i = 0; i < mGame->diceNum.getSize(); i++)
                    {
                        diceTriggered[i] = false;
                    }
                    for (int i = mGame->diceNum.getSize(); i < 8; i++)
                    {
                        diceTriggered[i] = true;
                    }
                }
                else {
                    CancelConsumingDice(mPoint);
                }
            }
            else {
                CancelConsumingDice(mPoint);
                for (int i = 0; i < mGame->diceNum.getSize(); i++)
                {
                    if (placedDice[i].isIn(mPoint.x, mPoint.y)) 
                    {
                        if (diceTriggered[i]) {     //取消选中骰子
                            diceTriggered[i] = 0;
                            int n = -1;
                            n += mGame->diceNum.m[ElementType::cai];
                            if (n >= i) {
                                diceTriggeredNum.m[ElementType::cai]--;
                            }
                            else {
                                vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
                                sort(vec.begin(), vec.end(), Cost::cmp);
                                for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
                                {
                                    if (it->first != ElementType::cai) {
                                        n += it->second;
                                        if (n >= i) {
                                            diceTriggeredNum.m[it->first]--;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            //选中骰子
                            int n = -1;
                            n += mGame->diceNum.m[ElementType::cai];
                            if (n >= i) {
                                if (!(diceTriggeredNum >= cost)) {
                                    diceTriggered[i] = true;
                                    mGame->diceTriggerred[selectedDiceNum++].setPos(placedDice[i].getPosX(), placedDice[i].getPosY());
                                    diceTriggeredNum.m[ElementType::cai]++;
                                }
                            }
                            else {
                                vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
                                sort(vec.begin(), vec.end(), Cost::cmp);
                                for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
                                {
                                    if (it->first != ElementType::cai) {
                                        n += it->second;
                                        if (n >= i) {
                                            if (diceTriggeredNum.m[it->first] < cost.m[it->first] + cost.m[ElementType::cai]) {
                                                diceTriggered[i] = true;
                                                mGame->diceTriggerred[selectedDiceNum++].setPos(placedDice[i].getPosX(), placedDice[i].getPosY());
                                                diceTriggeredNum.m[it->first]++;
                                            }
                                            break;
                                        }
                                    }
                                }
                            }

                            
                        }
                        cout << "使用技能 ：" << i << endl;
                        cout << "已经选择的骰子2" << endl;
                        for (auto i = diceTriggeredNum.m.begin(); i != diceTriggeredNum.m.end(); i++) {
                            cout << (int)(*i).first << " " << (*i).second << endl;
                        }
                        break;
                    }
                }

            }

        }
        else if (isCardTriggered)
        {
            if (Card* temp = mGame->cards.cardMouse(mPoint.x, mPoint.y))    //选择别的牌
            {
                if (temp!=triggeredCard)
                {
                    diceTriggeredNum = Cost();
                    triggeredCard = temp;
                    target = NULL;
                }
            }
            if (!triggeredCard->quickAction)    //先选人
            {
                bool haveChose = 0;
                for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
                {
                    if (it->isIn(mPoint.x,mPoint.y))
                    {
                        haveChose = 1;
                        target = &(*it);
                        cout << int((*it).getElementType())<<"dawdjaws" << endl;
                        if (triggeredCard->cardtype == CardType::equipment) {
                            if (target->getEquipmentType() == EquipmentType::单手剑 && triggeredCard->name == ConcreateCard::旅行剑
                                || target->getEquipmentType() == EquipmentType::大剑 && triggeredCard->name == ConcreateCard::白铁大剑
                                ) {     //当角色手中没有武器并且武器对上时才执行
                                triggeredCard->quickAction=true;
                            }
                        }
                        else if (triggeredCard->cardtype == CardType::relics) {
                            cout << int(target->getElementType()) << " " << int(triggeredCard->name) << endl;
                            if (target->getElementType() == ElementType::shui && triggeredCard->name == ConcreateCard::酒渍船帽
                                || target->getElementType() == ElementType::lei && triggeredCard->name == ConcreateCard::唤雷的头冠
                                || target->getElementType() == ElementType::bing && triggeredCard->name == ConcreateCard::破冰踏雪的回音
                                ) {
                                triggeredCard->quickAction = true;
                            }
                            
                        }
                        else {
                            triggeredCard->quickAction = true;
                        }
                        break;
                    }
                   
                    
                }
                if(!haveChose)
                    CancelConsumingDice(mPoint);
            }
            else {  //立即执行选骰子
                if (target == NULL)
                {
                    for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
                    {
                        if (it->IsSelected())
                        {
                            cout << "卡片选中对象" << endl;
                            target = &(*it);
                        }
                    }
                }
                else {
                    if (!(diceTriggeredNum >= triggeredCard->cost))
                    {
                        CancelConsumingDice(mPoint);
                        for (int i = 0; i < mGame->diceNum.getSize(); i++)
                        {
                            if (placedDice[i].isIn(mPoint.x, mPoint.y))
                            {
                                if (diceTriggered[i]) {
                                    diceTriggered[i] = 0;
                                    int n = -1;
                                    n += mGame->diceNum.m[ElementType::cai];
                                    if (n >= i) {
                                        diceTriggeredNum.m[ElementType::cai]--;
                                    }
                                    else {
                                        vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
                                        sort(vec.begin(), vec.end(), Cost::cmp);
                                        for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
                                        {
                                            if (it->first != ElementType::cai) {
                                                n += it->second;
                                                if (n >= i) {
                                                    diceTriggeredNum.m[it->first]--;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                                else {
                                    //选中骰子
                                    int n = -1;
                                    n += mGame->diceNum.m[ElementType::cai];
                                    if (n >= i) {
                                        if (!(diceTriggeredNum >= triggeredCard->cost)) {
                                            diceTriggered[i] = true;
                                            mGame->diceTriggerred[selectedDiceNum++].setPos(placedDice[i].getPosX(), placedDice[i].getPosY());
                                            diceTriggeredNum.m[ElementType::cai]++;
                                        }
                                    }
                                    else {
                                        vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
                                        sort(vec.begin(), vec.end(), Cost::cmp);
                                        for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
                                        {
                                            if (it->first != ElementType::cai) {
                                                n += it->second;
                                                if (n >= i) {
                                                    if (diceTriggeredNum.m[it->first] < triggeredCard->cost.m[it->first] + triggeredCard->cost.m[ElementType::cai]) {
                                                        diceTriggered[i] = true;
                                                        mGame->diceTriggerred[selectedDiceNum++].setPos(placedDice[i].getPosX(), placedDice[i].getPosY());
                                                        diceTriggeredNum.m[it->first]++;
                                                    }
                                                    break;
                                                }
                                            }
                                        }
                                    }


                                }
                                cout << "使用card ：" << i << endl;
                                cout << "已经选择的骰子" << endl;
                                for (auto i = diceTriggeredNum.m.begin(); i != diceTriggeredNum.m.end(); i++) {
                                    cout << (int)(*i).first << " " << (*i).second << endl;
                                }
                                break;
                            }
                        }
                    }
                    }
                        
                
                
                
            }
            
        }
        else if (isChangingRole)
        {
            Cost changingRoleCost(1, pair<ElementType, int>(ElementType::cai, 1));
            //处理换人的场景卡效果
            for (auto it = mGame->playerPlaceVector[1].begin(); it != mGame->playerPlaceVector[1].end(); it++)
            {
                switch ((*it).name)
                {
                case ConcreateCard::凯瑟琳:
                    if ((*it).times > 0)
                    {
                        quickChange = true;
                    }
                    (*it).times = 0;
                    break;
                case ConcreateCard::晨曦酒庄:
                    if ((*it).times > 0)
                    {
                        changingRoleCost = changingRoleCost - changingRoleCost;
                    }
                    (*it).times = 0;
                    break;
                default:
                    break;
                }
            }
            if (luoshayiya)
            {
                changingRoleCost = changingRoleCost - changingRoleCost;
                luoshayiya = false;
            }
            if (diceTriggeredNum >= changingRoleCost)  //换人的费用，可能不为1
            {
                if (mGame->changeConfirm.isIn(mPoint.x, mPoint.y))
                {
                    selectedDiceNum = 0;
                    mGame->diceNum = mGame->diceNum - diceTriggeredNum;
                    diceTriggeredNum = Cost();
                    for (int i = 0; i < mGame->diceNum.getSize(); i++)
                    {
                        diceTriggered[i] = false;
                    }
                    for (int i = mGame->diceNum.getSize(); i < 8; i++)
                    {
                        diceTriggered[i] = true;
                    }
                    isChanged = true;
                    isConsumingDice = false;
                }
                else {
                    CancelConsumingDice(mPoint);
                }
            }
            else {
                CancelConsumingDice(mPoint);
                for (int i = 0; i < mGame->diceNum.getSize(); i++)
                {
                    if (placedDice[i].isIn(mPoint.x, mPoint.y)) {
                        if (diceTriggered[i]) {
                            diceTriggered[i] = 0;
                            int n = -1;
                            n += mGame->diceNum.m[ElementType::cai];
                            if (n >= i) {
                                diceTriggeredNum.m[ElementType::cai]--;
                            }
                            else {
                                vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
                                sort(vec.begin(), vec.end(), Cost::cmp);
                                for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
                                {
                                    if (it->first != ElementType::cai) {
                                        n += it->second;
                                        if (n >= i) {
                                            diceTriggeredNum.m[it->first]--;
                                            break;
                                        }
                                    }
                                }
                            }
                        }

                        else {
                            //选中骰子
                            int n = -1;
                            n += mGame->diceNum.m[ElementType::cai];
                            if (n >= i) {
                                if (!(diceTriggeredNum >= changingRoleCost)) {
                                    diceTriggered[i] = true;
                                    diceTriggeredNum.m[ElementType::cai]++;
                                    mGame->diceTriggerred[selectedDiceNum++].setPos(placedDice[i].getPosX(), placedDice[i].getPosY());
                                }
                            }
                            else {
                                vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
                                sort(vec.begin(), vec.end(), Cost::cmp);
                                for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
                                {
                                    if (it->first != ElementType::cai) {
                                        n += it->second;
                                        if (n >= i) {
                                            mGame->diceTriggerred[selectedDiceNum++].setPos(placedDice[i].getPosX(), placedDice[i].getPosY());
                                            if (diceTriggeredNum.m[it->first] < changingRoleCost.m[it->first] + changingRoleCost.m[ElementType::cai]) {
                                                diceTriggered[i] = true;
                                                diceTriggeredNum.m[it->first]++;
                                            }
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        cout << "使用换人 ：" << i << endl;
                        cout << "已经选择的骰子2" << endl;
                        for (auto i = diceTriggeredNum.m.begin(); i != diceTriggeredNum.m.end(); i++) {
                            cout << (int)(*i).first << " " << (*i).second << endl;
                        }
                    }
                }

            }
        }
        
    }
    if (Card* temp = mGame->cards.cardMouse(mPoint.x, mPoint.y))
    {
        if (!isAbilityTriggered&&!isChangingRole&&!isCardTriggered&&!isCardFinished)
        {
            isCardTriggered = true;
            triggeredCard = temp;
            isConsumingDice = true;
            mGame->cards.setHeldCardsPosition(0.5 - mGame->cards.getCardNum() * cardWidth / 3, heldCardY-moveOffset, cardWidth * 0.9);
        }
    }
    for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++) {
        if (!isCardTriggered && it->isIn(mPoint.x, mPoint.y) && currentRole!=&(*it))
        {
            isChangingRole = true;
            target = &(*it);
            isConsumingDice = true;
            isAbilityTriggered = false;
        }
    }
    for (auto it = mGame->ui.begin(); it != mGame->ui.end(); it++) 
    {
        if (!isConsumingDice && it->isIn(mPoint.x, mPoint.y))
        {
            if (it->name == "turnMark")
            {
                mGame->firstConfirm = true;
            }
        }
    }
    for (auto i = mGame->sAbility.begin(); i != mGame->sAbility.end(); i++)
    {
        if (!isChangingRole && !isConsumingDice && (*i)->isIn(mPoint.x, mPoint.y))
        {
            if (i == mGame->sAbility.end() - 1 &&currentRole->getNp()== currentRole->maxNp()||i!= mGame->sAbility.end() - 1)
            {
                isConsumingDice = true;
                triggeredAbility = &(**i);
                target = mGame->CurrentEnemy();   //获取敌人，敌人多了修改这里。 
                isAbilityTriggered = true;
            }
         
        }
    }
}
void PlayerTurnState::RightButtonDown(Vector2i mPoint)
{
    //isConsumingDice = !isConsumingDice;
}
