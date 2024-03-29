#include "EnemyTurnState.h"
#include"Card.h"
EnemyTurnState::EnemyTurnState(Game* game) :State(game) {}
void EnemyTurnState::Input() {
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
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                if (isChangingRole)
                {
                    for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++) {
                        if (it->isIn(event.mouseButton.x, event.mouseButton.y))
                        {
                            changedCharacter = &(*it);
                        }
                    }
                    if (mGame->changeConfirm.isIn(event.mouseButton.x, event.mouseButton.y))
                    {
                        isChanged = true;
                        isChangingRole = false;
                    }
                }
            
            }
        }
    }
}
void EnemyTurnState::Logic() {
    if (bannertime < bannerTime)
    {
        bannertime++;
    }
    else {
        mGame->firstConfirm = true;
    }
    if (mGame->enemyAction <= 0)
    {
        mGame->enemyTurnOver = true;
    }
    if (isChanged)
    {
        if (changedCharacter != NULL)
        {
            changedCharacter->Selected(true,true);
            int num = 0;
            if (changedCharacter->name == "xingqiu")
            {
                for (auto i = 0; i < 3; i++)
                {
                    mGame->sAbility[i] = mGame->abilityVector[i];
                }
            }
            else if (changedCharacter->name == "keqing")
            {
                for (auto i = 0; i < 3; i++)
                {
                    mGame->sAbility[i] = mGame->abilityVector[i + 3];
                }
            }
            else if (changedCharacter->name == "kaiya")
            {
                for (auto i = 0; i < 3; i++)
                {
                    mGame->sAbility[i] = mGame->abilityVector[i + 6];
                }
            }
            changedCharacter = NULL;
            isChanged = false;
        }
    }
    else if (mGame->firstConfirm && !isChanged&&!isChangingRole)
    {
        if (times == 0)
        {
            for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++) {
                if (it->IsSelected())
                {
                    target = &(*it);
                }
            }
        }
        else if (times == 250 && !mGame->enemyTurnOver  && ! mGame->enemyVector[0].IsFrozen())    //敌人冰冻不许动
        {
            srand((unsigned)time(NULL));
            int rate = rand() % 100;
            if (rate >= 80)
            {
                target->getHurt(&mGame->enemyVector[0],4);
                showHurt = true;
                if (target->gethp() <= 0)
                {
                    target->Die();
                    for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++) {
                        it->Selected(false,true);
                    }
                    isChangingRole = true;
                }
                int lose = 0;
                for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++) {
                    if (!it->ifDead())
                    {
                        lose++;
                        break;
                    }

                }
                if (lose == 0)      //输了
                {
                    mGame->isWin = false;
                    mGame->ChangeState(new GameEndState(mGame));
                }

            }
            else if(rate >= 60){    //换人
                target = mGame->CurrentEnemy();
                target->Selected(false, false);
                for (auto it = mGame->enemyVector.begin(); ; it++)
                {
                    if (it == mGame->enemyVector.end())
                        it = mGame->enemyVector.begin();
                    random_device rd;
                    float r = rd() % 2;
                    if ((*it).gethp() > 0 && target!=&(*it)&&r>0.5)
                    {
                        (*it).Selected(true, false);
                        break;
                    }
                    
                }
            }
            else {
                //使用卡牌
                mGame->enemySummonedVector.push_back(new Summoned(ConcreateCard::敌方召唤物, 2, 2, windowWidth * placeCardWidth, windowHeight * placeCardHeight, mGame->texarr[350]));
            }
            
            
        }
        else if (times >= 500)
        {
          
            mGame->firstConfirm = false;
            mGame->enemyAction -= 1;
            if (!mGame->playerTurnOver)
            {
                cout << "Enemy回合结束，进入玩家回合" << endl;
                mGame->ChangeState(new PlayerTurnState(mGame));
            }
            else if (mGame->enemyTurnOver && mGame->playerTurnOver)
            {
                mGame->ChangeState( new TurnEndState(mGame));
            }
            else if (!mGame->enemyTurnOver && mGame->playerTurnOver)
            {
                mGame->ChangeState(new EnemyTurnState(mGame));
            }
                
        }
        times++;
    }

}
void EnemyTurnState::Draw() {

    mGame->window.clear();//清屏
    mGame->view.setSize(sf::Vector2f(mGame->window.getSize()));
    mGame->view.setCenter(sf::Vector2f(mGame->window.getSize()) / 2.f);
    mGame->window.setView(mGame->view);

    mGame->backGround.sprite.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
    mGame->backGround.draw(mGame->window);
    mGame->drawPlaceVector();

    mGame->summonedVectorAutoPlace();
    mGame->drawSummonedVector();

    for (auto it = mGame->ui.begin(); it != mGame->ui.end(); it++) {
        it->sprite.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
        it->draw(mGame->window);
    }

    for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++) {
        mGame->showElement(*it);
        it->draw(mGame->window, mGame->view.getSize().x / windowWidth * it->getScalex(), mGame->view.getSize().y / windowHeight * it->getScaley(), mGame->shader);
    }
    for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++) {
        mGame->showElement(*it);
        it->draw(mGame->window, mGame->view.getSize().x / windowWidth * it->getScalex(), mGame->view.getSize().y / windowHeight * it->getScaley(), mGame->shader);
    }

    //画骰子
    int n = 0;
    vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
    sort(vec.begin(), vec.end(), Cost::cmp);
    for (int i = 0; i < mGame->diceNum.m[ElementType::cai]; i++) {
        mGame->dices[n].sprite.setTexture(mGame->texarr[200]);
        mGame->dices[n].setScale(mGame->view.getSize().x / windowWidth * mGame->dices[i].getScalex(), mGame->view.getSize().y / windowHeight * mGame->dices[i].getScaley());
        mGame->dices[n].draw(mGame->window);
        n++;
    }
    for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it->first != ElementType::cai) {
            for (int i = 0; i < it->second; i++) {
                mGame->dices[n].sprite.setTexture(mGame->texarr[200 + (int)it->first]);
                mGame->dices[n].setScale(mGame->view.getSize().x / windowWidth * mGame->dices[i].getScalex(), mGame->view.getSize().y / windowHeight * mGame->dices[i].getScaley());
                mGame->dices[n].draw(mGame->window);
                n++;
            }
        }
    }

    if (bannertime < bannerTime)
    {
        mGame->enemybanner.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
         mGame->enemybanner.draw(mGame->window);
    }
    else {
        int times = 0;
        if (!isChangingRole)
        {
            for (auto it = mGame->sAbility.begin(); it != mGame->sAbility.end(); it++) {
                (*it)->Object::setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
                (*it)->Object::draw(mGame->window);
            }
        }
        
    
    }
    if (isChangingRole)
    {
        mGame->changeConfirm.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
        mGame->changeConfirm.draw(mGame->window);
        if (changedCharacter != NULL) {
            mGame->changeTarget.setPos((*changedCharacter).getX(), (*changedCharacter).getY());
            mGame->changeTarget.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->changeTarget.draw(mGame->window);
        }
    }
    if (showHurt)
    {
        int static damage;
        times = 251;
        if (hurtTimer == 0)
        {
            mGame->hurt.setPos((*target).getX() - 0.01, (*target).getY());
            damage=target->getHurtNum();
            
        }
        if (hurtTimer++ < hurtTime)
        {
            mGame->hurt.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->hurt.draw(mGame->window);

            Text text;
            text.setFont(font);
            text.setString('-' + to_string(damage));
            text.setPosition(mGame->window.getSize().x * ((*target).getX() - hpLeftOffset * 0), mGame->window.getSize().y * ((*target).getY() - hpLeftOffset * 4.8));
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
    mGame->cards.draw(mGame->window, mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
    mGame->window.display();//把显示缓冲区的内容，显示在屏幕上
}
