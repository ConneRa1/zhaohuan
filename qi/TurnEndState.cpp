#include "TurnEndState.h"
TurnEndState::TurnEndState(Game* game) :State(game) {
}
void TurnEndState::Input() {
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

    }
}
void TurnEndState::Logic() {
    if (bannertime < bannerTime)bannertime++;
    if (bannertime >= bannerTime)mGame->firstConfirm = true;
    if (mGame->firstConfirm)
    {
        if (times == 10) {
            int damege = 0;
            for (auto it = mGame->enemySummonedVector.begin(); it != mGame->enemySummonedVector.end(); it++) {
                damege += (*it)->num;
                (*it)->times--;
                if ((*it)->times == 0)
                    mGame->enemySummonedVector.erase(it);


            }
            if (damege > 0) {
                mGame->CurrentCharacter()->getHurt(damege);
                showHurt = true;
                
                
            }
        }

        if (times++ >= 500)
        {
            
            for (auto i = mGame->playerPlaceVector[3].begin(); i != mGame->playerPlaceVector[3].end(); i++)
            {
                for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++)
                {
                    it->setfrozen(false);
                    it->deleteBuff(BuffType::饱);
                }
                for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
                {
                    it->setfrozen(false);
                    it->deleteBuff(BuffType::饱);
                }
                int min = 10;
                switch ((*i).name)
                {
                case ConcreateCard::西风大教堂:
                    mGame->CurrentCharacter()->addHp(2);
                    healtarget = target;
                    healtimer = 200;
                    healNum = 2;
                    break;
                case ConcreateCard::望舒客栈:
                    target = NULL;
                    for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
                    {
                        if (&(*it) != mGame->CurrentCharacter() && (*it).gethp() < min)
                        {
                            min = (*it).gethp();
                            target = &(*it);
                        }
                    }
                    if (target) {
                        target->addHp(2);
                        healtarget = target;
                        healtimer = 200;
                        healNum = 2;
                    }
                    break;
                case ConcreateCard::璃月港口:
                    mGame->cards.drawCard();
                    mGame->cards.drawCard();
                    mGame->cards.autoPlace();
                    break;

                default:
                    break;
                }
            }
           
            mGame->resetPlaceCardTimes();   

            cout << "结束阶段结束，进入下一大回合" << endl;
            mGame->firstConfirm = false;
            mGame->ChangeState(new DrawCardState(mGame));
        }
    }

}
void TurnEndState::Draw() {
    mGame->window.clear();//清屏
    mGame->view.setSize(sf::Vector2f(mGame->window.getSize()));
    mGame->view.setCenter(sf::Vector2f(mGame->window.getSize()) / 2.f);
    mGame->window.setView(mGame->view);

    mGame->backGround.sprite.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
    mGame->backGround.draw(mGame->window);

    mGame->backGround.sprite.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
    mGame->backGround.draw(mGame->window);
    mGame->placeVectorAutoPlace();

    mGame->summonedVectorAutoPlace();
    mGame->drawSummonedVector();

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
    if (showHurt)
    {
        int static damage;
        times = 251;
        if (hurtTimer == 0)
        {
            mGame->hurt.setPos((*mGame->CurrentCharacter()).getX() - 0.01, (*mGame->CurrentCharacter()).getY());
            damage = mGame->CurrentCharacter()->getHurtNum();

        }
        if (hurtTimer++ < hurtTime)
        {
            mGame->hurt.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->hurt.draw(mGame->window);

            Text text;
            text.setFont(font);
            text.setString('-' + to_string(damage));
            text.setPosition(mGame->window.getSize().x * ((*mGame->CurrentCharacter()).getX() - hpLeftOffset * 0), mGame->window.getSize().y * ((*mGame->CurrentCharacter()).getY() - hpLeftOffset * 4.8));
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
    if (bannertime <  bannerTime) //先显示结束阶段
    {
       
        mGame->cards.draw(mGame->window, mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
        mGame->whenEnd.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
        mGame->whenEnd.draw(mGame->window);

    }

    mGame->window.display();//把显示缓冲区的内容，显示在屏幕上
}
