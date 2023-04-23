#include "ConsumeDiceState.h"
ConsumeDiceState::ConsumeDiceState(Game* game) :State(game){}
void ConsumeDiceState::Input() {
    Event event;
    if (!dicePlaced)
    {
        dicePlaced = true;
        placedDice.clear(); 
        //每次进入这个状态，都重置骰子的位子
        int flag = 0;
        for (int i = 0; i < mGame->diceNum; i++)
        {
            placedDice.push_back(mGame->chooseDice);
            if (flag % 2 == 0)
            {
                flag = 0;
            }
            flag++;
            placedDice[i].setPos(flag*consumeDiceOffsetX+consumeDiceX,consumeDiceY+(i/2)*consumeDiceOffsetY);
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


    }
}
void ConsumeDiceState::Logic() {
    if (mGame->firstConfirm)
    {
        if (times++ >= 500)
        {
            cout << "选择骰子结束，释放技能/卡牌" << endl;
            mGame->firstConfirm = false;
            mGame->ChangeState(new PlayerTurnState(mGame));
        }
    }

}
void ConsumeDiceState::Draw() {
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

    for (int i = 0; i < placedDice.size(); i++)
    {
        placedDice[i].setScale(mGame->view.getSize().x / windowWidth * placedDice[i].getScalex(), mGame->view.getSize().y / windowHeight * placedDice[i].getScaley());
        placedDice[i].draw(mGame->window);
    }
    int times = 0;
    for (auto it = mGame->sAbility.begin(); it != mGame->sAbility.end(); it++) {
        it->Object::setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
        it->Object::draw(mGame->window);
    }
    mGame->cards.draw(mGame->window, mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
    mGame->window.display();//把显示缓冲区的内容，显示在屏幕上
}
void ConsumeDiceState::LeftButtonDown(Vector2i mPoint)
{
    
}
