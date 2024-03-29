#include "FirstDiceState.h"
FirstDiceState::FirstDiceState(Game* game) :State(game){
}
void FirstDiceState::Input() {
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
            if (mGame->firstConfirm ==false&&mGame->confirmButton.isIn(Mouse::getPosition(mGame->window).x, Mouse::getPosition(mGame->window).y))
            {
                mGame->firstConfirm = true;

                //更新骰子
                mGame->diceNum = mGame->diceNum - diceTriggeredNum;
                cout << mGame->diceNum.m[ElementType::cai];
                for (int i = 0; i < diceTriggeredNum.getSize(); i++) {
                    random_device rd;
                    mGame->diceNum.m[ElementType(rd() % (int)ElementType::count)]++;
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
                //处理投掷骰子的场景卡效果
                for (auto it = mGame->playerPlaceVector[0].begin(); it != mGame->playerPlaceVector[0].end(); it++)
                {
                    if ((*it).times >0 &&(*it).name == ConcreateCard::骑士团图书馆)
                    {
                        (*it).times = 0;
                        mGame->firstConfirm = false;
                        diceTriggeredNum = Cost();
                        for(int x=0;x<8;x++)
                            rollDiceTriggered[x] = 0;
                    }
                }
            }
            if (mGame->firstInitDice == false && mGame->firstConfirm == false) {
                for (int i = 0; i < 8; i++)
                {
                    if (mGame->rollDices[i].isIn(Mouse::getPosition(mGame->window).x, Mouse::getPosition(mGame->window).y)) {
                        if (rollDiceTriggered[i]) {
                            rollDiceTriggered[i] = 0;
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
                        else 
                        {
                            //选中骰子
                            int n = -1;
                            n += mGame->diceNum.m[ElementType::cai];
                            if (n >= i) {
                                rollDiceTriggered[i] = true;
                                diceTriggeredNum.m[ElementType::cai]++;
                            }
                            else {
                                vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
                                sort(vec.begin(), vec.end(), Cost::cmp);
                                for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
                                {
                                    if (it->first != ElementType::cai) {
                                        n += it->second;
                                        if (n >= i) {
                                            rollDiceTriggered[i] = true;
                                            diceTriggeredNum.m[it->first]++;

                                            break;
                                        }
                                    }
                                }
                            }


                        }


                    }
                }
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

    }
}
void FirstDiceState::Logic() {
    mGame->initdice = false;
    if (bannertime < 1.5*bannerTime)bannertime++;
    if (mGame->firstInitDice) {
        mGame->firstInitDice = false;
        Cost temp;
        for (int i = 0; i < 8; i++) {
            random_device rd;
            temp.m[ElementType(rd() % (int)ElementType::count)]++;
            //temp.m[ElementType(0)]++;

        }

        mGame->diceNum = temp;
    }
    if (mGame->firstConfirm)
    {
        if (times++ >= 1.5 * bannerTime)
        {
            mGame->firstInitDice = true;
            cout << "投骰子结束，进入战斗" << endl;
            mGame->firstConfirm = false;

            mGame->enemyAction = 2;
            mGame->enemyTurnOver = false;
            mGame->playerTurnOver = false;
            if (mGame->isPlayerFirst)
                mGame->ChangeState(new PlayerTurnState(mGame));
            else
                mGame->ChangeState(new EnemyTurnState(mGame));
        }
    }

}
void FirstDiceState::Draw() {
    mGame->window.clear();//清屏
    mGame->view.setSize(sf::Vector2f(mGame->window.getSize()));
    mGame->view.setCenter(sf::Vector2f(mGame->window.getSize()) / 2.f);
    mGame->window.setView(mGame->view);

    if (mGame->initdice)
    {   
        mGame->backGround.sprite.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
        mGame->backGround.draw(mGame->window);

        //画骰子
        int n = 0;
        vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
        sort(vec.begin(), vec.end(), Cost::cmp);
        for (int i = 0; i < mGame->diceNum.m[ElementType::cai]; i++) {
            mGame->rollDices[n].sprite.setTexture(mGame->texarr[210]);
            mGame->rollDices[n].setScale(mGame->view.getSize().x / windowWidth * windowWidth * rolldiceWidth / (float)mGame->rollDices[n].sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * rolldiceHeight / (float)mGame->rollDices[n].sprite.getTexture()->getSize().y);
            mGame->rollDices[n].draw(mGame->window);
            n++;
        }
        for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
        {
            if (it->first != ElementType::cai) {
                for (int i = 0; i < it->second; i++) {
                    mGame->rollDices[n].sprite.setTexture(mGame->texarr[210+(int)it->first]);
                    mGame->rollDices[n].setScale(mGame->view.getSize().x / windowWidth * windowWidth * rolldiceWidth / (float)mGame->rollDices[n].sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * rolldiceHeight / (float)mGame->rollDices[n].sprite.getTexture()->getSize().y);
                    mGame->rollDices[n].draw(mGame->window);
                    n++;
                }
            }
        }

        mGame->confirmButton.setScale(mGame->view.getSize().x / windowWidth * (float)windowWidth * confirmButtonWidth / (float)mGame->confirmButton.sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * confirmButtonHeight / (float)mGame->confirmButton.sprite.getTexture()->getSize().y);
        mGame->confirmButton.draw(mGame->window);
        
    }
    else {
        if (bannertime <  bannerTime) {
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
            for (auto it = mGame->ui.begin(); it != mGame->ui.end(); it++) {
                it->sprite.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
                it->draw(mGame->window);
            }
            mGame->whenDice.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->whenDice.draw(mGame->window);
        }
        else {
            mGame->backGround.sprite.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->backGround.draw(mGame->window);

            //画骰子
            int n = 0;
            vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
            sort(vec.begin(), vec.end(), Cost::cmp);
            for (int i = 0; i < mGame->diceNum.m[ElementType::cai]; i++) {
                mGame->rollDices[n].sprite.setTexture(mGame->texarr[210]);
                mGame->rollDices[n].setScale(mGame->view.getSize().x / windowWidth * windowWidth * rolldiceWidth / (float)mGame->rollDices[n].sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * rolldiceHeight / (float)mGame->rollDices[n].sprite.getTexture()->getSize().y);
                mGame->rollDices[n].draw(mGame->window);
                n++;
            }
            for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
            {
                if (it->first != ElementType::cai) {
                    for (int i = 0; i < it->second; i++) {
                        mGame->rollDices[n].sprite.setTexture(mGame->texarr[210 + (int)it->first]);
                        mGame->rollDices[n].setScale(mGame->view.getSize().x / windowWidth * windowWidth * rolldiceWidth / (float)mGame->rollDices[n].sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * rolldiceHeight / (float)mGame->rollDices[n].sprite.getTexture()->getSize().y);
                        mGame->rollDices[n].draw(mGame->window);
                        n++;
                    }
                }
            }
            for (int i = 0; i < 8; i++)
            {
                if (rollDiceTriggered[i])
                {
                    mGame->rollDicesbg[i].setScale(mGame->view.getSize().x / windowWidth * windowWidth * rolldiceWidth / (float)mGame->rollDices[0].sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * rolldiceHeight / (float)mGame->rollDices[0].sprite.getTexture()->getSize().y);
                    mGame->rollDicesbg[i].setPos(mGame->rollDices[i].getPosX(), mGame->rollDices[i].getPosY());
                    mGame->rollDicesbg[i].draw(mGame->window);
                }
            }
            mGame->confirmButton.setScale(mGame->view.getSize().x / windowWidth * (float)windowWidth * confirmButtonWidth / (float)mGame->confirmButton.sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * confirmButtonHeight / (float)mGame->confirmButton.sprite.getTexture()->getSize().y);
            mGame->confirmButton.draw(mGame->window);
        
        }
       
        
        
     }
    mGame->window.display();//把显示缓冲区的内容，显示在屏幕上
}