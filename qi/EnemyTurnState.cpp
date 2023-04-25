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
            changedCharacter->Selected(true);
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
        else if (times == 250&&!mGame->enemyTurnOver&& mGame->enemyVector[0].IsFrozen())    //敌人冰冻不许动
        {
            /*for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++) {    //后续有多个敌人再加
                if(it->)
            }*/
            target->getHurt(5);
            showHurt = true;
            if (target->gethp() <= 0)
            {
                target->Die();
                for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++) {
                    it->Selected(false);
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
            //如果敌人数不为0，就加个CheckWin()
                //进入胜利界面
        }
        else if (times >= 700)
        {
           
            cout << "Enemy回合结束，进入玩家回合" << endl;
            mGame->firstConfirm = false;
            mGame->enemyAction -= 1;
            if (mGame->enemyTurnOver && mGame->playerTurnOver)
            {
                mGame->diceNum = Cost(1, pair<ElementType, int>(ElementType::cai, 8));
                mGame->ChangeState(new TurnEndState(mGame));
            }
            else if(!mGame->playerTurnOver)
                mGame->ChangeState( new PlayerTurnState(mGame));
            else {
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
    for (int i = 0; i < mGame->diceNum.getSize(); i++)    //按骰子数画
    {
        mGame->dices[i].setScale(mGame->view.getSize().x / windowWidth * mGame->dices[i].getScalex(), mGame->view.getSize().y / windowHeight * mGame->dices[i].getScaley());
        mGame->dices[i].draw(mGame->window);
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
        if (hurtTimer == 0)
        {
            mGame->hurt.setPos((*target).getX() - 0.01, (*target).getY());
            target = NULL;
        }
        if (hurtTimer++ < hurtTime)
        {
           
            mGame->hurt.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->hurt.draw(mGame->window);
        }
        else {
            hurtTimer = 0;
            showHurt = false;
        }
    }
    
    mGame->cards.draw(mGame->window, mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
    mGame->window.display();//把显示缓冲区的内容，显示在屏幕上
}
