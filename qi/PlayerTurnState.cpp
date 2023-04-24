#include "PlayerTurnState.h"
PlayerTurnState::PlayerTurnState(Game* game) :State(game){

}

void PlayerTurnState::Input() {
    if (bannertime >= bannerTime)
    {
        Event event;
        if (!flag)
        {
            mGame->cards.setHeldCardsPosition(0.5- mGame->cards.getCardNum()* cardWidth/4, heldCardY, cardWidth*0.52);
            flag = true;
            placedDice.clear();
            //每次进入这个状态，都重置骰子的位子
            int num = 0;
            /*for (int i = 0; i < mGame->diceNum; i++)
            {
                placedDice.push_back(mGame->chooseDice);
                if (num % 2 == 0)
                {
                    num = 0;
                }
                placedDice[i].setPos(num * consumeDiceOffsetX + consumeDiceX, consumeDiceY + (i / 2) * consumeDiceOffsetY);
                num++;
            }*/
            for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++) {
                if (it->IsSelected())
                {
                    currentRole = &(*it);
                    break;
                }
            }
        }
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
    if (mGame->firstConfirm)
    {
        if (times++ >= 500)
        {
            cout << "玩家回合结束" ;
            mGame->firstConfirm = false;
            mGame->playerTurnOver = true;
            if (!mGame->enemyTurnOver)
            {
                cout << "，进入enemy回合" << endl;
                mGame->ChangeState( new EnemyTurnState(mGame));
            }
            else
            {
                cout << "，进入下一回合" << endl;
                mGame->ChangeState(new FirstDiceState(mGame));
            }
                
        }
    }
    else if (isActed)
    {
        if (triggeredAbility != NULL && target != NULL)
        {
            cout << "玩家回合结束，进入enemy回合" << endl;
            target->getHurt(2);
            if (target->gethp() <= 0)
            {
                target->Die();
                //如果敌人数不为0，就加个CheckWin()
                //进入胜利界面
                mGame->isWin = true;
                mGame->ChangeState(new GameEndState(mGame));
            }
            else {
                mGame->ChangeState( new EnemyTurnState(mGame));
            }
           
            isActed = false;
        }
        else if(triggeredAbility != NULL && target != NULL){
            triggeredAbility = NULL;    
            target = NULL;
            isActed = false;
            cout << "骰子数不足" << endl;
        }
        target = NULL;
        triggeredAbility = NULL;
    }
    else if (isCardFinished)
    {
        //使用当前卡片
        isCardFinished = false;
        isCardTriggered = false;
        triggeredCard = NULL;
        target = NULL;
        //
        //
        // switch(typeof(card))
        // {
        // case 1:
        //      作相应的动作
        //  }
    }
    else if (isChanged)
    {
        isChanged = false;
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
        it->draw(mGame->window, mGame->view.getSize().x / windowWidth * it->getScalex(), mGame->view.getSize().y / windowHeight * it->getScaley(), mGame->shader);
    }
    for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++) {
        it->draw(mGame->window, mGame->view.getSize().x / windowWidth * it->getScalex(), mGame->view.getSize().y / windowHeight * it->getScaley(), mGame->shader);
    }

    if (isConsumingDice)
    {
        mGame->dicebg.setScale(mGame->view.getSize().x / windowWidth * (float)windowWidth * diceBgWidth / (float)mGame->dicebg.sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * diceBgHeight / (float)mGame->dicebg.sprite.getTexture()->getSize().y);
        mGame->dicebg.draw(mGame->window);
        /*for (int i = 0; i < mGame->diceNum ; i++)
        {
            placedDice[i].setScale(mGame->view.getSize().x / windowWidth * placedDice[i].getScalex(), mGame->view.getSize().y / windowHeight * placedDice[i].getScaley());
            placedDice[i].draw(mGame->window);
        }*/
        mGame->chupai.setScale(mGame->view.getSize().x / windowWidth * (float)windowWidth * confirmButtonWidth / (float)mGame->confirmButton.sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * confirmButtonHeight / (float)mGame->confirmButton.sprite.getTexture()->getSize().y);
        mGame->chupai.draw(mGame->window);
        
    }
    else {
        for (auto it = mGame->ui.begin(); it != mGame->ui.end(); it++) {
            it->sprite.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            it->draw(mGame->window);
        }
       /* for (int i = 0; i < mGame->diceNum; i++)
        {
            mGame->dices[i].setScale(mGame->view.getSize().x / windowWidth * mGame->dices[i].getScalex(), mGame->view.getSize().y / windowHeight * mGame->dices[i].getScaley());
            mGame->dices[i].draw(mGame->window);
        }*/
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
        mGame->cards.draw(mGame->window, mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
    }
    
    mGame->window.display();//把显示缓冲区的内容，显示在屏幕上
}
void PlayerTurnState::LeftButtonDown(Vector2i mPoint)   //什么时候要消耗骰子，！isCardTriggered 点击卡片，点击角色，！isAbilityTriggered 点击技能
{
    if (isConsumingDice)
    {
        if (!mGame->dicebg.isIn(mPoint.x, mPoint.y))
        {
            isConsumingDice = false;
            isAbilityTriggered = false;
            isCardTriggered = false;
            isChangingRole = false;
            target = NULL;
        }
        if (isAbilityTriggered)
        {
            //if (diceTriggeredNum >= triggeredAbility->cost)
            //{
            //    //if confirm
            //    mGame->diceNum -= triggeredAbility->cost;
            //    isActed = true;
            //    diceTriggeredNum = 0;
            //    isConsumingDice = false;
            //    for (int i = 0; i < mGame->diceNum; i++)
            //    {
            //        diceTriggered[i] = false;
            //    }
            //    for (int i = mGame->diceNum; i < 8; i++)
            //    {
            //        diceTriggered[i] = true;
            //    }
            //}
            //else {
            //    for (int i = 0; i < mGame->diceNum; i++)
            //    {
            //        if (!diceTriggered[i] && placedDice[i].isIn(mPoint.x, mPoint.y))
            //        {
            //            diceTriggered[i] = true;
            //            diceTriggeredNum += 1;
            //            cout << "使用技能 ： i" << "  已点击数：" << diceTriggeredNum << endl;
            //        }
            //    }

            //}

        }
        else if (isCardTriggered)
        {
            //if (diceTriggeredNum >= triggeredCard->cost)
            //{
            //    //if confirm
            //    mGame->diceNum -= triggeredCard->cost;
            //    isCardFinished = true;
            //    diceTriggeredNum = 0;
            //    isConsumingDice = false;
            //    for (int i = 0; i < mGame->diceNum; i++)
            //    {
            //        diceTriggered[i] = false;
            //    }
            //    for (int i = mGame->diceNum; i < 8; i++)
            //    {
            //        diceTriggered[i] = true;
            //    }
            //}
            //else {
            //    for (int i = 0; i < mGame->diceNum; i++)
            //    {
            //        if (!diceTriggered[i] && placedDice[i].isIn(mPoint.x, mPoint.y))
            //        {
            //            diceTriggered[i] = true;
            //            diceTriggeredNum += 1;
            //            cout << "使用卡牌 ： i" << "  已点击数：" << diceTriggeredNum << endl;
            //        }
            //    }

            //}
        }
        else if (isChangingRole)
        {
            if (diceTriggeredNum >= 1)  //换人的费用，可能不为1
            {
                //if confirm
                //mGame->diceNum -= 1;
                diceTriggeredNum = 0;
                /*for (int i = 0; i < mGame->diceNum; i++)
                {
                    diceTriggered[i] = false;
                }
                for (int i = mGame->diceNum; i < 8; i++)
                {
                    diceTriggered[i] = true;
                }*/
                isChanged = true;
                isConsumingDice = false;
            }
            else {
                /*for (int i = 0; i < mGame->diceNum; i++)
                {
                    if (!diceTriggered[i] && placedDice[i].isIn(mPoint.x, mPoint.y))
                    {
                        diceTriggered[i] = true;
                        diceTriggeredNum += 1;
                    }
                }*/

            }
        }
    }
    if (Card* temp = mGame->cards.cardMouse(mPoint.x, mPoint.y))
    {
        if (!isCardTriggered)
        {
            isCardTriggered = true;
            triggeredCard = temp;
            isConsumingDice = true;
            
            if (triggeredCard->quickAction)
            {
                for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
                {
                    if (it->IsSelected())
                    {
                        target = &(*it);
                        cout << "card" << endl;
                        isCardFinished = true;
                        isCardTriggered = false;
                        isConsumingDice = false;
                    }
                }
            }
            else {  //不是立刻的，需要选择使用对象

            }
            
        }
        else {  //要切换
            if (temp != triggeredCard)
            {
                triggeredCard = temp;
            }
            else {
                triggeredCard = NULL;
            }
        }
    }
    else {
        if (isCardTriggered)    
        {
            for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
            {
                if (it->isIn(mPoint.x, mPoint.y))
                {
                    target = &(*it);
                    isCardFinished = true;
                    isCardTriggered = false;
                }
            }
        }
    }
    for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++) {
        if (it->isIn(mPoint.x, mPoint.y)&&currentRole!=&(*it))
        {
            isChangingRole = true;
            target = &(*it);
            isConsumingDice = true;
            
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
            //if (!isConsumingDice&& i->isIn(mPoint.x, mPoint.y))
            //{
            //    isConsumingDice = true;
            //    //isActed = true;
            //    triggeredAbility = &(*i);
            //    target = & mGame->enemyVector[0];   //获取敌人，敌人多了修改这里。 
            //        isActed = true;
            //        target = &(*it);
            //        isAbilityTriggered = false;
            //        cout << "点击到了！" << endl;
            //}
        }
    }
    
    
    
}
void PlayerTurnState::RightButtonDown(Vector2i mPoint)
{
    isConsumingDice = !isConsumingDice;
}
