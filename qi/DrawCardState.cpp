#include "DrawCardState.h"
DrawCardState::DrawCardState(Game* game) :State(game) {}
void DrawCardState::Input() {
    Event event;

}
void DrawCardState::Logic() {
    //if(times)   ����ĳ��ʱ��Σ���������
    if (times >= 500)
    {
        cout << "���Ž�����������һغ�" << endl;
        mGame->ChangeState(new PlayerTurnState(mGame));
    }
    times++;
}

void DrawCardState::Draw() {
    mGame->window.clear();//����
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

    //������
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

    int times = 0;
    for (auto it = mGame->sAbility.begin(); it != mGame->sAbility.end(); it++) {
        (*it)->Object::setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
        (*it)->Object::draw(mGame->window);
    }
    mGame->cards.draw(mGame->window, mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
    mGame->window.display();//����ʾ�����������ݣ���ʾ����Ļ��
}

