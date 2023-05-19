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
        if (times++ >= 500)
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
            for (auto i = mGame->playerPlaceVector[3].begin(); i != mGame->playerPlaceVector[3].end(); i++)
            {
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
    if (bannertime <  bannerTime) //先显示结束阶段
    {
       
        mGame->cards.draw(mGame->window, mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
        mGame->whenEnd.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
        mGame->whenEnd.draw(mGame->window);

    }

    mGame->window.display();//把显示缓冲区的内容，显示在屏幕上
}
