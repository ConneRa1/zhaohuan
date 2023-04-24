#include "PlayerTurnState.h"
PlayerTurnState::PlayerTurnState(Game* game) :State(game){

}

void PlayerTurnState::Input() {
    if (bannertime >= bannerTime)
    {
        Event event;
        if (!flag)
        {
            mGame->cards.setHeldCardsPosition(0.5- mGame->cards.getCardNum()* cardWidth/4, heldCardY, cardWidth*0.52);
            flag = true;
            placedDice.clear();
            //ÿ�ν������״̬�����������ӵ�λ��
            int num = 0;
            for (int i = 0; i < mGame->diceNum.getSize(); i++)
            {
                placedDice.push_back(mGame->chooseDice);
                if (num % 2 == 0)
                {
                    num = 0;
                }
                placedDice[i].setPos(num * consumeDiceOffsetX + consumeDiceX, consumeDiceY + (i / 2) * consumeDiceOffsetY);
                num++;
            }
            for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++) {
                if (it->IsSelected())
                {
                    currentRole = &(*it);
                    break;
                }
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
    
}
void PlayerTurnState::Logic() {
    if (bannertime < bannerTime)bannertime++;
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
                mGame->diceNum = Cost(1, pair<ElementType, int>(ElementType::cai, 8));
                mGame->ChangeState(new FirstDiceState(mGame));
            }
                
        }
    }
    else if (hurtOver)
    {
        if (hurtTimer >= hurtTime)
        {
            if(mGame->isWin){
                mGame->ChangeState(new GameEndState(mGame));
            }
            else {
                mGame->ChangeState(new EnemyTurnState(mGame));
            }
        }
        
    }
    else if (isActed)
    {
        if (triggeredAbility != NULL && target != NULL)
        {
            cout << "��һغϽ���������enemy�غ�" << endl;
            target->getHurt(2);
            if (target->gethp() <= 0)
            {
                target->Die();
                //�����������Ϊ0���ͼӸ�CheckWin()
                //����ʤ������
                mGame->isWin = true;
            }
            hurtOver = true;
            isActed = false;
        }
        else if(triggeredAbility != NULL && target != NULL){
            triggeredAbility = NULL;    
            target = NULL;
            isActed = false;
            cout << "����������" << endl;
        }
        showHurt = true;
        triggeredAbility = NULL;
    }
    else if (isCardFinished)
    {
        //ʹ�õ�ǰ��Ƭ
        isCardFinished = false;
        isCardTriggered = false;
        triggeredCard = NULL;
        target = NULL;
        //
        //
        // switch(typeof(card))
        // {
        // case 1:
        //      ����Ӧ�Ķ���
        //  }
    }
    else if (isChanged)
    {
        if (times == 0)
        {
            isChangingRole = false;
            Character* c = (Character*) target;
            currentRole= (Character*)target;
            c->Selected(true);
            if (c->name == "xingqiu")
            {
                for (auto i = 0; i<3; i++)
                {
                    mGame->sAbility[i] = mGame->abilityVector[i];
                }
            }
            else if (c->name == "keqing")
            {
                for (auto i = 0; i < 3; i++)
                {

                    mGame->sAbility[i] = mGame->abilityVector[i+3];
                }
            }
            else if (c->name == "kaiya")
            {
                for (auto i = 0; i < 3; i++)
                {

                    mGame->sAbility[i] = mGame->abilityVector[i+6];
                }
            }
            for (auto i = mGame->characterVector.begin(); i != mGame->characterVector.end(); i++)
            {
                if (&(*i) != target)
                {
                    i->Selected(false);
                }
            }
            target = NULL;
        }
        
        if (quickChange)
        {
            isChanged = false;
        }
        else {
            if (times++ >= 500)
            {
                cout << "�������Ļغ�";
                if (!mGame->enemyTurnOver)
                {
                    cout << "������enemy�غ�" << endl;
                    mGame->ChangeState(new EnemyTurnState(mGame));
                }
                else
                {
                    cout << "��������һ�غ�" << endl;
                    mGame->ChangeState(new PlayerTurnState(mGame));
                }

            }
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
   
    for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++) {
        it->draw(mGame->window, mGame->view.getSize().x / windowWidth * it->getScalex(), mGame->view.getSize().y / windowHeight * it->getScaley(), mGame->shader);
    }
    for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++) {
        it->draw(mGame->window, mGame->view.getSize().x / windowWidth * it->getScalex(), mGame->view.getSize().y / windowHeight * it->getScaley(), mGame->shader);
    }
    if (isConsumingDice)
    {
        mGame->dicebg.setScale(mGame->view.getSize().x / windowWidth * (float)windowWidth * diceBgWidth / (float)mGame->dicebg.sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * diceBgHeight / (float)mGame->dicebg.sprite.getTexture()->getSize().y);
        mGame->dicebg.draw(mGame->window);
        for (int i = 0; i < mGame->diceNum.getSize() ; i++)
        {
            placedDice[i].setScale(mGame->view.getSize().x / windowWidth * placedDice[i].getScalex(), mGame->view.getSize().y / windowHeight * placedDice[i].getScaley());
            placedDice[i].draw(mGame->window);
        }
        mGame->chupai.setScale(mGame->view.getSize().x / windowWidth * (float)windowWidth * confirmButtonWidth / (float)mGame->confirmButton.sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * confirmButtonHeight / (float)mGame->confirmButton.sprite.getTexture()->getSize().y);
        mGame->chupai.draw(mGame->window);
        if (isAbilityTriggered)
        {
            mGame->target.setPos((*target).getX(), (*target).getY());
            mGame->target.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->target.draw(mGame->window);
        }
    }
    else {
        for (auto it = mGame->ui.begin(); it != mGame->ui.end(); it++) {
            it->sprite.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            it->draw(mGame->window);
        }
        for (int i = 0; i < mGame->diceNum.getSize(); i++)
        {
            mGame->dices[i].setScale(mGame->view.getSize().x / windowWidth * mGame->dices[i].getScalex(), mGame->view.getSize().y / windowHeight * mGame->dices[i].getScaley());
            mGame->dices[i].draw(mGame->window);
        }
        if (bannertime < bannerTime)
        {
            mGame->cards.setHeldCardsPosition(0.5 - mGame->cards.getCardNum() * cardWidth / 4, heldCardY, cardWidth * 0.52);
            mGame->playerbanner.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->playerbanner.draw(mGame->window);
        }
        else {
            if (isChangingRole)
            {
                mGame->changeConfirm.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
                mGame->changeConfirm.draw(mGame->window);
                mGame->changeTarget.setPos((*target).getX(), (*target).getY());
                mGame->changeTarget.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
                mGame->changeTarget.draw(mGame->window);
            }
            else {
                for (auto it = mGame->sAbility.begin(); it != mGame->sAbility.end(); it++) {
                   (*it)->Object::setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
                    (*it)->Object::draw(mGame->window);
                }
            }
            

        }
        mGame->cards.draw(mGame->window, mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
    }
    if (showHurt)
    {
        if (hurtTimer == 0)
        {
            mGame->hurt.setPos((*target).getX() - 0.01, (*target).getY());
            target = NULL;
        }
        if (hurtTimer++ < hurtTime)
        {
            mGame->hurt.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->hurt.draw(mGame->window);
        }
        else {
            hurtTimer = 0;
            showHurt = false;
        }
    }
    
    mGame->window.display();
}
void PlayerTurnState::LeftButtonDown(Vector2i mPoint)   //ʲôʱ��Ҫ�������ӣ���isCardTriggered �����Ƭ�������ɫ����isAbilityTriggered �������
{
    if (isChangingRole) //���˲�����ʾѡ����״̬����confirmֱ�Ӽ�1
    {
        if (mGame->diceNum >= Cost(1, pair<ElementType, int>(ElementType::cai, 1)))  //���˵ķ��ã����ܲ�Ϊ1
        {
            //if confirm
            if (mGame->changeConfirm.isIn(mPoint.x, mPoint.y))
            {
                mGame->diceNum = mGame->diceNum - Cost(1, pair<ElementType, int>(ElementType::cai, 1));
                diceTriggeredNum = Cost(1, pair<ElementType, int>(ElementType::cai, 0));
                for (int i = 0; i < mGame->diceNum.getSize(); i++)
                {
                    diceTriggered[i] = false;
                }
                for (int i = mGame->diceNum.getSize(); i < 8; i++)
                {
                    diceTriggered[i] = true;
                }
                isChanged = true;
               
            }
            
        }
        else {
            cout << "����������1����׼����" << endl;
            isChangingRole = false;
        }
    }
    if (isConsumingDice)
    {
        if (!mGame->dicebg.isIn(mPoint.x, mPoint.y))
        {
            isConsumingDice = false;
            isAbilityTriggered = false;
            isCardTriggered = false;

            target = NULL;
            for (int i = 0; i < mGame->diceNum.getSize(); i++)
            {
                diceTriggered[i] = false;
            }
        }
        if (isAbilityTriggered)
        {
            if (diceTriggeredNum >= triggeredAbility->cost)
            {
                //if confirm
                mGame->diceNum = mGame->diceNum - triggeredAbility->cost;
                isActed = true;
                diceTriggeredNum= Cost(1, pair<ElementType, int>(ElementType::cai, 0));
                isConsumingDice = false;
                for (int i = 0; i < mGame->diceNum.getSize(); i++)
                {
                    diceTriggered[i] = false;
                }
                for (int i = mGame->diceNum.getSize(); i < 8; i++)
                {
                    diceTriggered[i] = true;
                }
            }
            else {
                for (int i = 0; i < mGame->diceNum.getSize(); i++)
                {
                    if (!diceTriggered[i] && placedDice[i].isIn(mPoint.x, mPoint.y))
                    {
                        diceTriggered[i] = true;
                        diceTriggeredNum = diceTriggeredNum + Cost(1, pair<ElementType, int>(ElementType::cai, 1));
                        cout << "ʹ�ü��� ��"<< i  << endl;
                    }
                }

            }

        }
        else if (isCardTriggered)
        {
            //if (diceTriggeredNum >= triggeredCard->cost)
            //{
            //    //if confirm
            //    mGame->diceNum -= triggeredCard->cost;
            //    isCardFinished = true;
            //    diceTriggeredNum = 0;
            //    isConsumingDice = false;
            //    for (int i = 0; i < mGame->diceNum; i++)
            //    {
            //        diceTriggered[i] = false;
            //    }
            //    for (int i = mGame->diceNum; i < 8; i++)
            //    {
            //        diceTriggered[i] = true;
            //    }
            //}
            //else {
            //    for (int i = 0; i < mGame->diceNum; i++)
            //    {
            //        if (!diceTriggered[i] && placedDice[i].isIn(mPoint.x, mPoint.y))
            //        {
            //            diceTriggered[i] = true;
            //            diceTriggeredNum += 1;
            //            cout << "ʹ�ÿ��� �� i" << "  �ѵ������" << diceTriggeredNum << endl;
            //        }
            //    }

            //}
        }
        
    }
    if (Card* temp = mGame->cards.cardMouse(mPoint.x, mPoint.y))
    {
        if (!isCardTriggered)
        {
            isCardTriggered = true;
            triggeredCard = temp;
            isConsumingDice = true;
            
            if (triggeredCard->quickAction)
            {
                for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
                {
                    if (it->IsSelected())
                    {
                        target = &(*it);
                        cout << "card" << endl;
                        isCardFinished = true;
                        isCardTriggered = false;
                        isConsumingDice = false;
                    }
                }
            }
            else {  //�������̵ģ���Ҫѡ��ʹ�ö���

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
        if (it->isIn(mPoint.x, mPoint.y)&&currentRole!=&(*it))
        {
            isChangingRole = true;
            target = &(*it);

            
        }
       
    }
    for (auto it = mGame->ui.begin(); it != mGame->ui.end(); it++) 
    {
        if (!isConsumingDice && it->isIn(mPoint.x, mPoint.y))
        {
            if (it->name == "turnMark")
            {
                mGame->firstConfirm = true;
            }
           
        }
    }
    for (auto i = mGame->sAbility.begin(); i != mGame->sAbility.end(); i++)
    {
        if (!isConsumingDice && !isChangingRole && (*i)->isIn(mPoint.x, mPoint.y))
        {
            isConsumingDice = true;
            //isActed = true;
            triggeredAbility = &(**i);
            target = &mGame->enemyVector[0];   //��ȡ���ˣ����˶����޸���� 
            isAbilityTriggered = true;
        }
    }
        
    
    
    
}
void PlayerTurnState::RightButtonDown(Vector2i mPoint)
{
    isConsumingDice = !isConsumingDice;
}
