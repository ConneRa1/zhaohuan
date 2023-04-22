#include "EnemyTurnState.h"
#include"Card.h"
EnemyTurnState::EnemyTurnState(Game* game) :State(game) {}
void EnemyTurnState::Input() {
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
             mGame->firstConfirm = true;
        }


    }
}
void EnemyTurnState::Logic() {
    if (times == 0)
    {
        for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++) {
            if (it->IsSelected())
            {
                target = &(*it);
            }
        }
    }
    else if (times == 250)
    {
        target->getHurt(5);
        if (target->gethp() <= 0)
        {
            target->Die();
        }
        //进入换人阶段，到时候再加一个State

    }
    if (mGame->enemyAction == 0)
    {
        mGame->enemyTurnOver = true;
    }
    if (mGame->firstConfirm)
    {
        if (times++ >= 500)
        {
           
            cout << "Enemy回合结束，进入玩家回合" << endl;
            mGame->firstConfirm = false;
            mGame->enemyAction -= 1;
            if (mGame->enemyTurnOver && mGame->playerTurnOver)
            {
                mGame->ChangeState( new FirstDiceState(mGame));
            }
            else
                mGame->ChangeState( new PlayerTurnState(mGame));
        }
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
        it->draw(mGame->window, mGame->view.getSize().x / windowWidth * it->getScalex(), mGame->view.getSize().y / windowHeight * it->getScaley(), mGame->shader);
    }
    for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++) {
        it->draw(mGame->window, mGame->view.getSize().x / windowWidth * it->getScalex(), mGame->view.getSize().y / windowHeight * it->getScaley(), mGame->shader);
    }
    for (int i = 0; i < mGame->diceNum; i++)    //按骰子数画
    {
        mGame->dices[i].setScale(mGame->view.getSize().x / windowWidth * mGame->dices[i].getScalex(), mGame->view.getSize().y / windowHeight * mGame->dices[i].getScaley());
        mGame->dices[i].draw(mGame->window);
    }
    int times = 0;
    for (auto it = mGame->sAbility.begin(); it != mGame->sAbility.end(); it++) {
        it->Object::setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
        it->Object::draw(mGame->window);
    }
    mGame->cards.draw(mGame->window, mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
    mGame->window.display();//把显示缓冲区的内容，显示在屏幕上
}
