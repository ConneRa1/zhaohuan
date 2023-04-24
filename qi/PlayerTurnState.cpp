#include "PlayerTurnState.h"
PlayerTurnState::PlayerTurnState(Game* game) :State(game){

}

void PlayerTurnState::Input() {
    Event event;
    static bool flag = false;
    if (!flag)
    {
        mGame->cards.setHeldCardsPosition(0.5- mGame->cards.getCardNum()* cardWidth/4, heldCardY, cardWidth*0.52);
        flag = true;
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
    
    static int times = 0;
    if (mGame->firstConfirm)
    {
        if (times++ >= 500)
        {
            cout << "��һغϽ���" ;
            mGame->firstConfirm = false;
            mGame->playerTurnOver = true;
            if (!mGame->enemyTurnOver)
            {
                cout << "������enemy�غ�" << endl;
                mGame->ChangeState( new EnemyTurnState(mGame));
            }
            else
            {
                cout << "��������һ�غ�" << endl;
                mGame->ChangeState(new FirstDiceState(mGame));
            }
                
        }
    }
    else if (isActed)
    {
        if (triggeredAbility != NULL && target != NULL&& mGame->diceNum >= triggeredAbility->cost)
        {
            cout << "��һغϽ���������enemy�غ�" << endl;;
           /* mGame->diceNum -= triggeredAbility->cost;*/
            target->getHurt(2);
            if (target->gethp() <= 0)
            {
                target->Die();
            }
            mGame->ChangeState( new EnemyTurnState(mGame));
        }
        else if(triggeredAbility != NULL && target != NULL){
            triggeredAbility = NULL;    
            target = NULL;
            isActed = false;
            cout << "����������" << endl;
        }
    }
}
void PlayerTurnState::Draw() {
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

    /*for (int i = 0; i < mGame->diceNum; i++)
    {
        mGame->dices[i].setScale(mGame->view.getSize().x / windowWidth * mGame->dices[i].getScalex(), mGame->view.getSize().y / windowHeight * mGame->dices[i].getScaley());
        mGame->dices[i].draw(mGame->window);
    }*/
    int times = 0;
    for (auto it = mGame->sAbility.begin(); it != mGame->sAbility.end(); it++) {
        (*it)->Object::setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
        (*it)->Object::draw(mGame->window);
    }
    mGame->cards.draw(mGame->window, mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
    mGame->window.display();//����ʾ�����������ݣ���ʾ����Ļ��
}
void PlayerTurnState::LeftButtonDown(Vector2i mPoint)
{
    if (Card* temp = mGame->cards.cardMouse(mPoint.x, mPoint.y))
    {
        if (!isCardTriggered)
        {
            isCardTriggered = true;
            triggeredCard = temp;
            if (temp->quickAction)
            {
                for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
                {
                    if (it->IsSelected())
                    {
                        target = &(*it);
                        cout << "card" << endl;
                        isCardFinished = true;
                        isCardTriggered = false;
                    }
                }
            }
        }
        else {  //Ҫ�л�
            if (temp != triggeredCard)
            {
                triggeredCard = temp;
            }
            else {
                triggeredCard = NULL;
            }
        }
    }
    else {
        if (isCardTriggered)    
        {
            for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
            {
                if (it->isIn(mPoint.x, mPoint.y))
                {
                    target = &(*it);
                    isCardFinished = true;
                    isCardTriggered = false;
                }

            }
        }
    }
    for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++) {
        if (it->isIn(mPoint.x, mPoint.y))
        {
            int i;
            it->Selected(true);
            int times = 0;
            if (it->name == "xingqiu")
            {
                for (i = 0; i < 3; i++) {
                    mGame->sAbility[i] = mGame->abilityVector[i];
                }
            }
            else if (it->name == "keqing")
            {
                for (i = 0; i < 3; i++) {
                    mGame->sAbility[i] = mGame->abilityVector[i+3];
                }
            }
            else if (it->name == "kaiya")
            {
                for (i = 0; i < 3; i++) {
                    mGame->sAbility[i] = mGame->abilityVector[i+6];
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
            if (it->name == "turnMark")
            {
                mGame->firstConfirm = true;
            }
        }

    }
    for (auto i = mGame->sAbility.begin(); i != mGame->sAbility.end(); i++)
    {
        if ((*i)->isIn(mPoint.x, mPoint.y))
        {
            isAbilityTriggered = true;      //�����
            triggeredAbility = *i;
        }
    }
    for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++)
    {
        if (isAbilityTriggered)
        {
            if (it->isIn(mPoint.x, mPoint.y))   
            {
                isActed = true;
                target = &(*it);
                isAbilityTriggered = false;
                cout << "������ˣ�" << endl;
            }
        }
        
    }
    
    
    
}
void PlayerTurnState::RightButtonDown(Vector2i mPoint)
{
    
}
