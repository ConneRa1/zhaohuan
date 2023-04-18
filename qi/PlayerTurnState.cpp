#include "PlayerTurnState.h"
PlayerTurnState::PlayerTurnState(Game* game) :State(game){
}
void PlayerTurnState::Input() {
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
            LeftButtonDown(Mouse::getPosition(mGame->window));
        }
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right)
        {
            RightButtonDown(Mouse::getPosition(mGame->window));
        }
        /* if (event.type == Event::EventType::KeyReleased && event.key.code == Keyboard::Add)
         {
             soundVolume += 5;
             bkMusic.setVolume(soundVolume);
         }
         if (event.type == Event::EventType::KeyReleased && event.key.code == Keyboard::Subtract)
         {
             soundVolume -= 5;
             bkMusic.setVolume(soundVolume);
         }
         if (event.type == Event::EventType::KeyReleased && event.key.code == Keyboard::Z)
         {
             system("pause");
         }
         if (event.type == Event::EventType::KeyPressed && event.key.code == Keyboard::Multiply || event.key.code == Keyboard::Enter)
         {
             if (MusicOn)
             {
                 bkMusic.stop();
             }
             else {
                 bkMusic.play();
             }
             MusicOn = !MusicOn;
         }*/
    }
}
void PlayerTurnState::Logic() {

}
void PlayerTurnState::Draw() {
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
    for (auto it = mGame->dices.begin(); it != mGame->dices.end(); it++)
    {
        it->sprite.setScale(mGame->view.getSize().x / windowWidth * it->getScalex(), mGame->view.getSize().y / windowHeight * it->getScaley());
        it->draw(mGame->window, mGame->shader);
    }
    int times = 0;
    for (auto it = mGame->sAbility.begin(); it != mGame->sAbility.end(); it++) {
        it->sprite.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
        it->draw(mGame->window);
    }
    mGame->window.display();//把显示缓冲区的内容，显示在屏幕上
}
void PlayerTurnState::LeftButtonDown(Vector2i mPoint)
{
    for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++) {
        if (it->isIn(mPoint.x, mPoint.y))
        {
            it->Selected(true);
            int times = 0;
            if (it->name == "xingqiu")
            {
                for (auto i = mGame->sAbility.begin(); i != mGame->sAbility.end(); i++)
                {
                    i->sprite.setTexture(mGame->texarr[150 + (times++)]);

                }
            }
            else if (it->name == "keqing")
            {
                for (auto i = mGame->sAbility.begin(); i != mGame->sAbility.end(); i++)
                {
                    i->sprite.setTexture(mGame->texarr[153 + (times++)]);

                }
            }
            else if (it->name == "kaiya")
            {
                for (auto i = mGame->sAbility.begin(); i != mGame->sAbility.end(); i++)
                {
                    i->sprite.setTexture(mGame->texarr[156 + (times++)]);

                }
            }
            for (auto i = mGame->characterVector.begin(); i != mGame->characterVector.end(); i++)
            {
                if (i != it)
                {
                    i->Selected(false);
                }
            }
        }
    }
    for (auto it = mGame->ui.begin(); it != mGame->ui.end(); it++) {
        if (it->isIn(mPoint.x, mPoint.y))
        {
            cout << it->name << endl;
        }
    }
    for (auto i = mGame->sAbility.begin(); i != mGame->sAbility.end(); i++)
    {
        if (i->isIn(mPoint.x, mPoint.y))
        {
            cout << "ability" << endl;
        }

    }
}
void PlayerTurnState::RightButtonDown(Vector2i mPoint)
{
    
}
