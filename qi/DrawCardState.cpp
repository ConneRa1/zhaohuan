#include "DrawCardState.h"
DrawCardState::DrawCardState(Game* game) :State(game) {}
void DrawCardState::Input() {
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
    }
}
void DrawCardState::Logic() {
    //if(times)   处于某个时间段，做个动画
    if (times >= drawCardTime+150)
    {
        cout << "1111抽牌结束，进入战斗回合" << endl;
        mGame->ChangeState(new FirstDiceState(mGame));
        times = drawCardTime;
    }
}

void DrawCardState::Draw() {
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
        it->draw(mGame->window, mGame->view.getSize().x / windowWidth * it->getScalex(), mGame->view.getSize().y / windowHeight * it->getScaley(), mGame->shader);
    }
    for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++) {
        it->draw(mGame->window, mGame->view.getSize().x / windowWidth * it->getScalex(), mGame->view.getSize().y / windowHeight * it->getScaley(), mGame->shader);
    }

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

    for (auto it = mGame->sAbility.begin(); it != mGame->sAbility.end(); it++) {
        (*it)->Object::setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
        (*it)->Object::draw(mGame->window);
    }
    //开始做动画
    if (times == 0)
    {
        startPosition1 = Vector2f(0.295, 0.356);
        startPosition2 = Vector2f(0.586, 0.356);
        endPosition1 = Vector2f(0.5 + (mGame->cards.getCardNum() ) * cardWidth / 4, heldCardY);
        endPosition2 = Vector2f(0.5 + (mGame->cards.getCardNum() + 2) * cardWidth / 4, heldCardY);
        card1 = mGame->cards.getCard(0);
        card2 = mGame->cards.getCard(1);
        
    }
    else if (times <drawCardTime)
    {

        float interpolation = (float)times / drawCardTime;
        //cout << interpolation << endl;
        Vector2f currentPosition1 = startPosition1 + (endPosition1 - startPosition1) * interpolation;
        Vector2f currentPosition2 = startPosition2+ (endPosition2 - startPosition2) * interpolation;
        card1->setPos(currentPosition1.x, currentPosition1.y);
        card2->setPos(currentPosition2.x, currentPosition2.y);
        card1->draw(mGame->window, mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
        card2->draw(mGame->window, mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
    }
    else if (times == drawCardTime)
    {
        mGame->cards.drawCard();
        mGame->cards.drawCard();
    }
    times++;
    mGame->cards.setHeldCardsPosition(0.5 - (mGame->cards.getCardNum() + 2) * cardWidth / 4, heldCardY, cardWidth * 0.52);
    mGame->cards.draw(mGame->window, mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
    mGame->window.display();
}

