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
    static int times = 0;
    if (mGame->firstConfirm)
    {
        if (times++ >= 500)
        {
            cout << "投骰子结束，进入战斗" << endl;
            mGame->firstConfirm = false;
            mGame->mState = new PlayerTurnState(mGame);
        }
    }
}
void FirstDiceState::Draw() {
    mGame->window.clear();//清屏
    mGame->view.setSize(sf::Vector2f(mGame->window.getSize()));
    mGame->view.setCenter(sf::Vector2f(mGame->window.getSize()) / 2.f);
    mGame->window.setView(mGame->view);

    mGame->backGround.sprite.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
    mGame->backGround.draw(mGame->window);
    for (auto it = mGame->rollDices.begin(); it != mGame->rollDices.end(); it++) {
        it->sprite.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight );
        it->draw(mGame->window);
    }
    mGame->confirmButton.setScale(mGame->view.getSize().x / windowWidth * (float)windowWidth * confirmButtonWidth / (float)mGame->confirmButton.sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * confirmButtonHeight / (float)mGame->confirmButton.sprite.getTexture()->getSize().y);
    mGame->confirmButton.draw(mGame->window);

    mGame->window.display();//把显示缓冲区的内容，显示在屏幕上
}