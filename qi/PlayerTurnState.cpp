#include "PlayerTurnState.h"
PlayerTurnState::PlayerTurnState(Game* game) :State(game){

}

void PlayerTurnState::HandleCard(Card* c) {
    //食物的加buff示例
    /*a1.addBuff(Buff(1, BuffType::盾, 2, 36, 36, texarr[110]));
    a1.addBuff(Buff(1, BuffType::加攻, 2, 36, 36, texarr[111]));
    a1.addBuff(Buff(1, BuffType::饱, 1, 36, 36, texarr[112]));*/
    int num = 0;
    switch (c->name)
    {
    //event
    case ConcreateCard::最好的伙伴:

        break;
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
    //food
    case ConcreateCard::仙跳墙:
        target->addBuff(Buff(1, BuffType::饱, 1, 36, 36, mGame->texarr[112]));
        target->addBuff(Buff(1, BuffType::大招, 1, 36, 36, mGame->texarr[111]));
        //target->addBuff()
        break;
    case ConcreateCard::土豆饼:
        target->addBuff(Buff(1, BuffType::饱, 1, 36, 36, mGame->texarr[112]));
        target->addHp(2);
        break;
    case ConcreateCard::烧鸡:
        target->addBuff(Buff(1, BuffType::饱, 1, 36, 36, mGame->texarr[112]));
        target->addHp(1);
        break;
    //场地
    
    //装备
    
    //圣遗物
    
    }
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
                if (&(*it) != mGame->CurrentEnemy())
                {
                    it->getHurt(1);	//后面改一下，只扣后台的
                }
                
            }
        }
        else {
            for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
            {
                if (&(*it) != mGame->CurrentCharacter())
                {
                    it->getHurt(1);	//后面改一下，只扣后台的
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
                if (&(*it) != mGame->CurrentEnemy())
                {
                    it->getHurt(1);	//后面改一下，只扣后台的
                }

            }
        }
        else {
            for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
            {
                if (&(*it) != mGame->CurrentCharacter())
                {
                    it->getHurt(1);	//后面改一下，只扣后台的
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
            if (event.type == Event::EventType::KeyReleased && event.key.code == Keyboard::X)
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
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right)
            {
                RightButtonDown(Mouse::getPosition(mGame->window));
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
                mGame->ChangeState(new FirstDiceState(mGame));
            }
        }
    }
    else if (hurtOver)
    {
        if (hurtTimer >= hurtTime*0.75)
        {
            //hurtTimer = 0;
            if (target->checkReact((*triggeredAbility).getElement()))     //有反应进反应
            {
                cout << "有元素反应" << endl;
                reactHurtOver = true;
                showReact = true;
                reactType = target->doReact((*triggeredAbility).getElement());
                doReact(reactType, true);

            }
            else {
                if(mGame->isWin){
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
            }
            cout << "玩家回合结束，进入enemy回合" << endl;
            //融入元素反应
            //先判断能否反应，不能：直接减、挂元素，能：元素反应，给出reacthurt,先正常伤害，再接上反应伤害
            target = mGame->CurrentEnemy(); 
            target->getHurt(currentRole,(*triggeredAbility).getDamage(),triggeredAbility==*(mGame->sAbility.end()-1));
            if (target->gethp() <= 0)
            {
                target->Die();
                //如果敌人数不为0，就加个CheckWin()
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
        mGame->cards.autoPlace();
    }
    else if (isChanged)
    {
        if (times == 0)
        {
            Character* c = (Character*) target;
            currentRole= (Character*)target;
            c->Selected(true);
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
                if (&(*i) != target)
                {
                    i->Selected(false);
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

    if (isConsumingDice)
    {
        mGame->dicebg.setScale(mGame->view.getSize().x / windowWidth * (float)windowWidth * diceBgWidth / (float)mGame->dicebg.sprite.getTexture()->getSize().x,
            mGame->view.getSize().y / windowHeight * (float)windowHeight * diceBgHeight / (float)mGame->dicebg.sprite.getTexture()->getSize().y);
        mGame->dicebg.draw(mGame->window);
        for (int i = 0; i < selectedDiceNum; i++)
        {
            mGame->diceTriggerred[i].draw(mGame->window);
        }
        int n = 0;
        vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
        sort(vec.begin(), vec.end(), Cost::cmp);
        for (int i = 0; i < mGame->diceNum.m[ElementType::cai]; i++) {
            placedDice[n].sprite.setTexture(mGame->texarr[200]);
            placedDice[i].setScale(mGame->view.getSize().x / windowWidth * placedDice[i].getScalex(), mGame->view.getSize().y / windowHeight * placedDice[i].getScaley());
            placedDice[n].draw(mGame->window);
            n++;
        }
        for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
        {
            if (it->first != ElementType::cai) {
                for (int i = 0; i < it->second; i++) {
                    placedDice[n].sprite.setTexture(mGame->texarr[200 + (int)it->first]);
                    placedDice[i].setScale(mGame->view.getSize().x / windowWidth * placedDice[i].getScalex(), mGame->view.getSize().y / windowHeight * placedDice[i].getScaley());
                    placedDice[n].draw(mGame->window);
                    n++;
                }
            }
        }
        if (isAbilityTriggered)
        {
            mGame->target.setPos((*target).getX(), (*target).getY());
            mGame->target.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->target.draw(mGame->window);
            mGame->chupai.setScale(mGame->view.getSize().x / windowWidth * (float)windowWidth * confirmButtonWidth / (float)mGame->confirmButton.sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * confirmButtonHeight / (float)mGame->confirmButton.sprite.getTexture()->getSize().y);
            mGame->chupai.draw(mGame->window);
        }
        else if (isCardTriggered)
        {
            //mGame->cards.setHeldCardsPositionY();
            mGame->chupai.setScale(mGame->view.getSize().x / windowWidth * (float)windowWidth * confirmButtonWidth / (float)mGame->confirmButton.sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * confirmButtonHeight / (float)mGame->confirmButton.sprite.getTexture()->getSize().y);
            mGame->chupai.draw(mGame->window);
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
            damage=target->getHurtNum();
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
            if (diceTriggeredNum >= triggeredAbility->cost)
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
                                if (!(diceTriggeredNum >= triggeredAbility->cost)) {
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
                                            if (diceTriggeredNum.m[it->first] < triggeredAbility->cost.m[it->first] + triggeredAbility->cost.m[ElementType::cai]) {
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
            if (!triggeredCard->quickAction)    //先选人
            {
                for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
                {
                    if (it->isIn(mPoint.x,mPoint.y))
                    {
                        target = &(*it);
                        triggeredCard->quickAction = true;
                    }
                }
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
                    if (diceTriggeredNum >= triggeredCard->cost)
                    {
                        //if confirm
                        if (CheckChupai(mPoint))
                        {
                            selectedDiceNum = 0;
                            mGame->diceNum = mGame->diceNum - triggeredCard->cost;
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
                            CancelConsumingDice(mPoint);
                        }

                    }
                    else {
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
        }
        else if (!isAbilityTriggered &&! isChangingRole && !isCardFinished){  //要切换
            if (temp != triggeredCard)
            {
                triggeredCard = temp;
            }
            else {
                //triggeredCard = NULL;
            }
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
