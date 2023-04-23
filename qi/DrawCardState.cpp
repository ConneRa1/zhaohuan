#include "DrawCardState.h"
DrawCardState::DrawCardState(Game* game) :State(game) {}
void DrawCardState::Input() {
    Event event;

}
void DrawCardState::Logic() {
    //if(times)   处于某个时间段，做个动画
    if (times >= 500)
    {
        cout << "抽排结束，进入玩家回合" << endl;
        mGame->ChangeState(new PlayerTurnState(mGame));
    }
    times++;
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

