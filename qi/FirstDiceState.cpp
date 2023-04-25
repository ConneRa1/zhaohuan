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
            if (mGame->confirmButton.isIn(Mouse::getPosition(mGame->window).x, Mouse::getPosition(mGame->window).y))
            {
                mGame->firstConfirm = true;
            }

        }


    }
}
void FirstDiceState::Logic() {
    if (bannertime < 1.5*bannerTime)bannertime++;
    if (mGame->firstInitDice) {
        mGame->firstInitDice = false;
        Cost temp;
        for (int i = 0; i < 8; i++) {
            random_device rd;
            temp.m[ElementType(rd() % (int)ElementType::count)]++;

        }
        mGame->diceNum = temp;
        //cout << mGame->diceNum.m[ElementType::cai] << endl;
        //mGame->diceNum = 8;     //初始化骰子数，和敌人行动力
    }
    if (mGame->firstConfirm)
    {
        if (times++ >= 500)
        {
            mGame->firstInitDice = true;
            mGame->initdice = false;
            cout << "投骰子结束，进入战斗" << endl;
            mGame->firstConfirm = false;

            mGame->enemyAction = 2;
            mGame->enemyTurnOver = false;
            mGame->playerTurnOver = false;
            mGame->ChangeState( new PlayerTurnState(mGame));
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

        /*for (auto it = mGame->rollDices.begin(); it != mGame->rollDices.end(); it++) {
            it->sprite.setScale(mGame->view.getSize().x / windowWidth * windowWidth * rolldiceWidth / (float)(*it).sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * rolldiceHeight / (float)(*it).sprite.getTexture()->getSize().y);
            it->draw(mGame->window);
        }*/

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

            mGame->cards.draw(mGame->window, mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
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

            mGame->confirmButton.setScale(mGame->view.getSize().x / windowWidth * (float)windowWidth * confirmButtonWidth / (float)mGame->confirmButton.sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * confirmButtonHeight / (float)mGame->confirmButton.sprite.getTexture()->getSize().y);
            mGame->confirmButton.draw(mGame->window);
        
        }
       
        
        
     }
    mGame->window.display();//把显示缓冲区的内容，显示在屏幕上
}