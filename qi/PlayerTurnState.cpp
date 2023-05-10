#include "PlayerTurnState.h"
PlayerTurnState::PlayerTurnState(Game* game) :State(game){

}

void PlayerTurnState::HandleCard(Card* c) {
    //ʳ��ļ�buffʾ��
    /*a1.addBuff(Buff(1, BuffType::��, 2, 36, 36, texarr[110]));
    a1.addBuff(Buff(1, BuffType::�ӹ�, 2, 36, 36, texarr[111]));
    a1.addBuff(Buff(1, BuffType::��, 1, 36, 36, texarr[112]));*/
    int num = 0;
    switch (c->name)
    {
    //event
    case ConcreateCard::��õĻ��:

        break;
    case ConcreateCard::�����Ұ�:
        quickChange = true;
        break; 
    case ConcreateCard::����֮��:
        for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
        {
            if (it->getNp() >= 1 && &(*it)!=mGame->CurrentCharacter())
            {
                it->setNp(it->getNp() - 1);
                num++;
            }
            mGame->CurrentCharacter()->setNp(mGame->CurrentCharacter()->getNp() + num);
        }
        break;
    case ConcreateCard::Ī��:
        mGame->CurrentCharacter()->setNp(mGame->CurrentCharacter()->getNp() + 1);
        break;
    case ConcreateCard::�׹�:

        break;
    //food
    case ConcreateCard::����ǽ:
        target->addBuff(Buff(1, BuffType::��, 1, 36, 36, mGame->texarr[112]));
        target->addBuff(Buff(1, BuffType::����, 1, 36, 36, mGame->texarr[111]));
        //target->addBuff()
        break;
    case ConcreateCard::������:
        target->addBuff(Buff(1, BuffType::��, 1, 36, 36, mGame->texarr[112]));
        target->addHp(2);
        break;
    case ConcreateCard::�ռ�:
        target->addBuff(Buff(1, BuffType::��, 1, 36, 36, mGame->texarr[112]));
        target->addHp(1);
        break;
    //����
    
    //װ��
    
    //ʥ����
    
    }
}
void PlayerTurnState::doReact(ReactType r, bool toEnemy)
{
    switch (r)
    {
    case ReactType::����:
        target->getHurt(2);
        break;
    case ReactType::�е�:
        if (toEnemy)
        {
            for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++)
            {
                if (&(*it) != mGame->CurrentEnemy())
                {
                    it->getHurt(1);	//�����һ�£�ֻ�ۺ�̨��
                }
                
            }
        }
        else {
            for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
            {
                if (&(*it) != mGame->CurrentCharacter())
                {
                    it->getHurt(1);	//�����һ�£�ֻ�ۺ�̨��
                }
            }
        }
        break;
    case ReactType::����:
        target->setfrozen(true);
        if (mGame->isWin) {
            mGame->ChangeState(new GameEndState(mGame));
        }
        else {
            mGame->ChangeState(new EnemyTurnState(mGame));
        }
        cout << "����!" << endl;
        break;
    case ReactType::����:
        cout << "����" << endl;
        if (toEnemy)
        {
            for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++)
            {
                if (&(*it) != mGame->CurrentEnemy())
                {
                    it->getHurt(1);	//�����һ�£�ֻ�ۺ�̨��
                }

            }
        }
        else {
            for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
            {
                if (&(*it) != mGame->CurrentCharacter())
                {
                    it->getHurt(1);	//�����һ�£�ֻ�ۺ�̨��
                }
            }
        }
        break;
    default:
        break;
    }


}
void PlayerTurnState::Input() {
    if (bannertime >= bannerTime)
    {
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
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::S)
            {
                cout << "�浵!" << endl;
                mGame->GetMemento();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num1)
            {
                mGame->LoadMemento(0);
                cout << "����1" << endl;
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
    if (bannertime >= bannerTime)
    {
        if (!flag)
        {
            mGame->cards.setHeldCardsPosition(0.5 - mGame->cards.getCardNum() * cardWidth / 4, heldCardY, cardWidth * 0.52);
            flag = true;
            placedDice.clear();
            //ÿ�ν������״̬�����������ӵ�λ��
            int num = 0;
            /*for (auto i = mGame->diceNum.m.begin(); i != mGame->diceNum.m.end(); i++) {
                cout << (*i).first << " " << (*i).second << endl;
            }*/
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
    }
    if (mGame->firstConfirm)
    {
        if (times++ >= 500)
        {
            cout << "��һغϽ���" ;
            mGame->playerTurnOver = true;
            mGame->firstConfirm = false;
            if (!mGame->enemyTurnOver)
            {
                mGame->isPlayerFirst = true;
                cout << "������enemy�غ�" << endl;
                mGame->ChangeState( new EnemyTurnState(mGame));
            }
            else
            {
                mGame->isPlayerFirst = false;
                cout << "��������һ�غ�" << endl;
                mGame->ChangeState(new FirstDiceState(mGame));
            }
        }
    }
    else if (hurtOver)
    {
        if (hurtTimer >= hurtTime*0.75)
        {
            //hurtTimer = 0;
            if (target->checkReact((*triggeredAbility).getElement()))     //�з�Ӧ����Ӧ
            {
                cout << "��Ԫ�ط�Ӧ" << endl;
                reactHurtOver = true;
                showReact = true;
                reactType = target->doReact((*triggeredAbility).getElement());
                doReact(reactType, true);

            }
            else {
                if(mGame->isWin){
                    mGame->ChangeState(new GameEndState(mGame));
                }
                else {
                    if (!mGame->enemyTurnOver)
                    {
                        mGame->ChangeState(new EnemyTurnState(mGame));
                    }
                    else {
                        mGame->ChangeState(new TurnEndState(mGame));
                    
                    }
                    
                }
            }
            hurtOver = false;
        }
    }
    else if (reactHurtOver)
    {
        if (delayTimer > hurtTime / 2)//��ʱ���з�Ӧ
        {
            if (reactHurtTimer >= hurtTime)
            {
                reactHurtTimer = 0;
                if (mGame->isWin) {
                    mGame->ChangeState(new GameEndState(mGame));
                }
                else {
                    if (!mGame->enemyTurnOver)
                    {
                        mGame->ChangeState(new EnemyTurnState(mGame));
                    }
                    else {
                        mGame->ChangeState(new TurnEndState(mGame));

                    }
                }
            }

        }
        
    }
    else if (isActed)
    {

        if (triggeredAbility != NULL && target != NULL)
        {
            if (triggeredAbility != *(mGame->sAbility.end() - 1))
            {
                currentRole->setNp(currentRole->getNp() + 1);
            }
            else {
                currentRole->setNp(0);
            }
            cout << "��һغϽ���������enemy�غ�" << endl;
            //����Ԫ�ط�Ӧ
            //���ж��ܷ�Ӧ�����ܣ�ֱ�Ӽ�����Ԫ�أ��ܣ�Ԫ�ط�Ӧ������reacthurt,�������˺����ٽ��Ϸ�Ӧ�˺�
            target = mGame->CurrentEnemy(); 
            target->getHurt(currentRole,(*triggeredAbility).getDamage(),triggeredAbility==*(mGame->sAbility.end()-1));
            if (target->gethp() <= 0)
            {
                target->Die();
                //�����������Ϊ0���ͼӸ�CheckWin()
                //����ʤ������
                mGame->isWin = true;
                mGame->ChangeState(new GameEndState(mGame));
            }
            /*else {
                mGame->ChangeState( new EnemyTurnState(mGame));
            }*/
           
            isActed = false;
        }
        hurtOver = true;
        showHurt = true;
    }
    else if (isCardFinished)
    {
        //ʹ�õ�ǰ��Ƭ
        isCardFinished = false;
        isCardTriggered = false;
        isConsumingDice = false;

        HandleCard(triggeredCard);
        mGame->cards.useCard(triggeredCard);
        mGame->cards.autoPlace();
        triggeredCard = NULL;
        mGame->cards.autoPlace();
    }
    else if (isChanged)
    {
        if (times == 0)
        {
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
            isChangingRole = false;
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
        mGame->showElement(*it);
        it->draw(mGame->window, mGame->view.getSize().x / windowWidth * it->getScalex(), mGame->view.getSize().y / windowHeight * it->getScaley(), mGame->shader);
    }
    for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++) {
        mGame->showElement(*it);
        it->draw(mGame->window, mGame->view.getSize().x / windowWidth * it->getScalex(), mGame->view.getSize().y / windowHeight * it->getScaley(), mGame->shader);
    }

    if (isConsumingDice)
    {
        mGame->dicebg.setScale(mGame->view.getSize().x / windowWidth * (float)windowWidth * diceBgWidth / (float)mGame->dicebg.sprite.getTexture()->getSize().x,
            mGame->view.getSize().y / windowHeight * (float)windowHeight * diceBgHeight / (float)mGame->dicebg.sprite.getTexture()->getSize().y);
        mGame->dicebg.draw(mGame->window);
        for (int i = 0; i < selectedDiceNum; i++)
        {
            mGame->diceTriggerred[i].draw(mGame->window);
        }
        int n = 0;
        vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
        sort(vec.begin(), vec.end(), Cost::cmp);
        for (int i = 0; i < mGame->diceNum.m[ElementType::cai]; i++) {
            placedDice[n].sprite.setTexture(mGame->texarr[200]);
            placedDice[i].setScale(mGame->view.getSize().x / windowWidth * placedDice[i].getScalex(), mGame->view.getSize().y / windowHeight * placedDice[i].getScaley());
            placedDice[n].draw(mGame->window);
            n++;
        }
        for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
        {
            if (it->first != ElementType::cai) {
                for (int i = 0; i < it->second; i++) {
                    placedDice[n].sprite.setTexture(mGame->texarr[200 + (int)it->first]);
                    placedDice[i].setScale(mGame->view.getSize().x / windowWidth * placedDice[i].getScalex(), mGame->view.getSize().y / windowHeight * placedDice[i].getScaley());
                    placedDice[n].draw(mGame->window);
                    n++;
                }
            }
        }
        if (isAbilityTriggered)
        {
            mGame->target.setPos((*target).getX(), (*target).getY());
            mGame->target.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->target.draw(mGame->window);
            mGame->chupai.setScale(mGame->view.getSize().x / windowWidth * (float)windowWidth * confirmButtonWidth / (float)mGame->confirmButton.sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * confirmButtonHeight / (float)mGame->confirmButton.sprite.getTexture()->getSize().y);
            mGame->chupai.draw(mGame->window);
        }
        else if (isCardTriggered)
        {
            //mGame->cards.setHeldCardsPositionY();
            mGame->chupai.setScale(mGame->view.getSize().x / windowWidth * (float)windowWidth * confirmButtonWidth / (float)mGame->confirmButton.sprite.getTexture()->getSize().x, mGame->view.getSize().y / windowHeight * (float)windowHeight * confirmButtonHeight / (float)mGame->confirmButton.sprite.getTexture()->getSize().y);
            mGame->chupai.draw(mGame->window);
        }
        else if (isChangingRole)
        {
            mGame->changeConfirm.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->changeConfirm.draw(mGame->window);
            mGame->changeTarget.setPos((*target).getX(), (*target).getY());
            mGame->changeTarget.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->changeTarget.draw(mGame->window);
        }
    }
    else {
        mGame->cards.draw(mGame->window, mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
        for (auto it = mGame->ui.begin(); it != mGame->ui.end(); it++) {
            it->sprite.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            it->draw(mGame->window);
        }
        int n = 0;
        vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
        sort(vec.begin(), vec.end(), Cost::cmp);
        for (int i = 0; i < mGame->diceNum.m[ElementType::cai]; i++) {
            mGame->dices[n].sprite.setTexture(mGame->texarr[200]);
            n++;
        }
        for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
        {
            if (it->first != ElementType::cai) {
                for (int i = 0; i < it->second; i++) {
                    mGame->dices[n].sprite.setTexture(mGame->texarr[200 + (int)it->first]);
                    n++;
                }
            }
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
            
                for (auto it = mGame->sAbility.begin(); it != mGame->sAbility.end(); it++) {
                    (*it)->Object::setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
                    (*it)->Object::draw(mGame->window);
                }
        }
    }
    if (showHurt)
    {
        int static damage;
        if (hurtTimer == 0)
        {
            damage=target->getHurtNum();
            mGame->hurt.setPos((*target).getX() - 0.01, (*target).getY());
            
        }
        if (hurtTimer++ < hurtTime * 0.75)
        {
            mGame->hurt.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
            mGame->hurt.draw(mGame->window);

            Text text;
            text.setFont(font);
            text.setString('-'+to_string(damage));
            text.setPosition(mGame->window.getSize().x* ((*target).getX()-hpLeftOffset*0), mGame->window.getSize().y* ((*target).getY() - hpLeftOffset *4.8));
            text.setFillColor(Color::White);
            text.setCharacterSize(float(mGame->window.getSize().y) / float(windowHeight) * fontSize * 4.5);
            mGame->window.draw(text);
        }
        else {
            //hurtTimer = 0;
            showHurt = false;
            //showReact = true;
        }
    }
    else if (showReact)
    {
        if (delayTimer++ > hurtTime / 2)
        {
            if (reactHurtTimer++ < hurtTime)
            {
                

                Text text;
                Text textReact;
                text.setFont(font);
                text.setCharacterSize(float(mGame->window.getSize().y) / float(windowHeight) * fontSize * 4.5);
                textReact.setFont(font);
                textReact.setCharacterSize(float(mGame->window.getSize().y) / float(windowHeight) * fontSize);
                switch (reactType)
                {
                case ReactType::����:
                    mGame->hurt.setPos((*target).getX() - 0.01, (*target).getY());
                    mGame->hurt.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
                    mGame->hurt.draw(mGame->window);

                    text.setString('-'+to_string(2));
                    text.setFillColor(Color::Blue);
                    text.setPosition(mGame->window.getSize().x* ((*target).getX() - hpLeftOffset * 0), mGame->window.getSize().y* ((*target).getY() - hpLeftOffset * 4.8));
                    mGame->window.draw(text);

                    textReact.setString("Vaporize");
                    textReact.setFillColor(Color::Blue);
                    textReact.setPosition(mGame->window.getSize().x* ((*target).getX() - hpLeftOffset * 0.1), mGame->window.getSize().y* ((*target).getY() + hpLeftOffset * 4));
                    mGame->window.draw(textReact);

                    
                    break;
                case ReactType::�е�:
                    text.setString('-' + to_string(1));
                    text.setFillColor(Color(128, 0, 128));

                    textReact.setString("Electro-Charged");
                    textReact.setFillColor(Color(128, 0, 128));
                    for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++)        //������һ�£�ֻ�ۺ�̨
                    {
                        mGame->hurt.setPos(it->getX() - 0.01, it->getY());
                        mGame->hurt.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
                        mGame->hurt.draw(mGame->window);
                        text.setPosition(mGame->window.getSize().x* (it->getX() - hpLeftOffset * 0), mGame->window.getSize().y* (it->getY() - hpLeftOffset * 4.8));
                        mGame->window.draw(text);

                        textReact.setPosition(mGame->window.getSize().x* ((*target).getX() + hpLeftOffset * 0.1), mGame->window.getSize().y* ((*target).getY() + hpLeftOffset * 4));
                        mGame->window.draw(textReact);
                    }
                    break;
                case ReactType::����:
                    text.setString('-' + to_string(1));
                    text.setFillColor(Color::White);

                    textReact.setString("Superconduct");
                    textReact.setFillColor(Color::White);
                    for (auto it = mGame->enemyVector.begin(); it != mGame->enemyVector.end(); it++)        //������һ�£�ֻ�ۺ�̨
                    {
                        mGame->hurt.setPos(it->getX() - 0.01, it->getY());
                        mGame->hurt.setScale(mGame->view.getSize().x / windowWidth, mGame->view.getSize().y / windowHeight);
                        mGame->hurt.draw(mGame->window);
                        text.setPosition(mGame->window.getSize().x * (it->getX() - hpLeftOffset * 0), mGame->window.getSize().y * (it->getY() - hpLeftOffset * 4.8));
                        mGame->window.draw(text);

                        textReact.setPosition(mGame->window.getSize().x* ((*target).getX() - hpLeftOffset * 0.1), mGame->window.getSize().y* ((*target).getY() + hpLeftOffset * 4));
                        mGame->window.draw(textReact);
                    }
                    break;
                case ReactType::����:
                    
                    textReact.setString("Frozen");
                    textReact.setFillColor(Color(86,193,254));
                    textReact.setPosition(mGame->window.getSize().x * ((*target).getX() - hpLeftOffset *1), mGame->window.getSize().y * ((*target).getY() + hpLeftOffset * 4));
                    mGame->window.draw(textReact);
                    break;
                default:
                    break;
                }
                


                
                
            }
            else {
                target = NULL;
                //reactHurtTimer = 0;
                showReact = false;
            }
        }
    }
    mGame->window.display();
}

void PlayerTurnState::CancelConsumingDice(Vector2i mPoint)
{
    if (!mGame->dicebg.isIn(mPoint.x, mPoint.y))
    {
        selectedDiceNum = 0;
        isConsumingDice = false;
        isAbilityTriggered = false;
        isCardTriggered = false;
        isChangingRole = false;
        target = NULL;
        diceTriggeredNum = Cost();
        mGame->cards.autoPlace();
        for (int i = 0; i < mGame->diceNum.getSize(); i++)
        {
            diceTriggered[i] = false;
        }
    }
}
bool PlayerTurnState::CheckChupai(Vector2i mPoint)
{
    if (mGame->chupai.isIn(mPoint.x, mPoint.y))
    {
        return true;
    }
    return false;
}
void PlayerTurnState::LeftButtonDown(Vector2i mPoint)   //ʲôʱ��Ҫ�������ӣ���isCardTriggered �����Ƭ�������ɫ����isAbilityTriggered �������
{
    if (isConsumingDice)
    {
        if (isAbilityTriggered)
        {
            if (diceTriggeredNum >= triggeredAbility->cost)
            {
                cout << "yes" << endl;
                if (CheckChupai(mPoint))
                {
                    selectedDiceNum = 0;
                    target = mGame->CurrentEnemy(); //����target���ȷ�ϻ����Լ�������ô��
                    mGame->diceNum = mGame->diceNum - diceTriggeredNum;
                    isActed = true;
                    isConsumingDice = false;
                    diceTriggeredNum = Cost();
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
                    CancelConsumingDice(mPoint);
                }
            }
            else {
                CancelConsumingDice(mPoint);
                for (int i = 0; i < mGame->diceNum.getSize(); i++)
                {
                    if (placedDice[i].isIn(mPoint.x, mPoint.y)) 
                    {
                        if (diceTriggered[i]) {     //ȡ��ѡ������
                            diceTriggered[i] = 0;
                            int n = -1;
                            n += mGame->diceNum.m[ElementType::cai];
                            if (n >= i) {
                                diceTriggeredNum.m[ElementType::cai]--;
                            }
                            else {
                                vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
                                sort(vec.begin(), vec.end(), Cost::cmp);
                                for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
                                {
                                    if (it->first != ElementType::cai) {
                                        n += it->second;
                                        if (n >= i) {
                                            diceTriggeredNum.m[it->first]--;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            //ѡ������
                            int n = -1;
                            n += mGame->diceNum.m[ElementType::cai];
                            if (n >= i) {
                                if (!(diceTriggeredNum >= triggeredAbility->cost)) {
                                    diceTriggered[i] = true;
                                    mGame->diceTriggerred[selectedDiceNum++].setPos(placedDice[i].getPosX(), placedDice[i].getPosY());
                                    diceTriggeredNum.m[ElementType::cai]++;
                                }
                            }
                            else {
                                vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
                                sort(vec.begin(), vec.end(), Cost::cmp);
                                for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
                                {
                                    if (it->first != ElementType::cai) {
                                        n += it->second;
                                        if (n >= i) {
                                            if (diceTriggeredNum.m[it->first] < triggeredAbility->cost.m[it->first] + triggeredAbility->cost.m[ElementType::cai]) {
                                                diceTriggered[i] = true;
                                                mGame->diceTriggerred[selectedDiceNum++].setPos(placedDice[i].getPosX(), placedDice[i].getPosY());
                                                diceTriggeredNum.m[it->first]++;
                                            }
                                            break;
                                        }
                                    }
                                }
                            }

                            
                        }
                        cout << "ʹ�ü��� ��" << i << endl;
                        cout << "�Ѿ�ѡ�������2" << endl;
                        for (auto i = diceTriggeredNum.m.begin(); i != diceTriggeredNum.m.end(); i++) {
                            cout << (int)(*i).first << " " << (*i).second << endl;
                        }
                        break;
                    }
                }

            }

        }
        else if (isCardTriggered)
        {
            if (!triggeredCard->quickAction)    //��ѡ��
            {
                for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
                {
                    if (it->isIn(mPoint.x,mPoint.y))
                    {
                        target = &(*it);
                        triggeredCard->quickAction = true;
                    }
                }
            }
            else {  //����ִ��ѡ����
                if (target == NULL)
                {
                    for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++)
                    {
                        if (it->IsSelected())
                        {
                            cout << "��Ƭѡ�ж���" << endl;
                            target = &(*it);
                        }
                    }
                }
                else {
                    if (diceTriggeredNum >= triggeredCard->cost)
                    {
                        //if confirm
                        if (CheckChupai(mPoint))
                        {
                            selectedDiceNum = 0;
                            mGame->diceNum = mGame->diceNum - triggeredCard->cost;
                            isCardFinished = true;
                            isCardTriggered = false;
                            isConsumingDice = false;
                            diceTriggeredNum = Cost();
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
                            CancelConsumingDice(mPoint);
                        }

                    }
                    else {
                        CancelConsumingDice(mPoint);
                        for (int i = 0; i < mGame->diceNum.getSize(); i++)
                        {
                            if (placedDice[i].isIn(mPoint.x, mPoint.y))
                            {
                                if (diceTriggered[i]) {
                                    diceTriggered[i] = 0;
                                    int n = -1;
                                    n += mGame->diceNum.m[ElementType::cai];
                                    if (n >= i) {
                                        diceTriggeredNum.m[ElementType::cai]--;
                                    }
                                    else {
                                        vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
                                        sort(vec.begin(), vec.end(), Cost::cmp);
                                        for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
                                        {
                                            if (it->first != ElementType::cai) {
                                                n += it->second;
                                                if (n >= i) {
                                                    diceTriggeredNum.m[it->first]--;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                                else {
                                    //ѡ������
                                    int n = -1;
                                    n += mGame->diceNum.m[ElementType::cai];
                                    if (n >= i) {
                                        if (!(diceTriggeredNum >= triggeredCard->cost)) {
                                            diceTriggered[i] = true;
                                            mGame->diceTriggerred[selectedDiceNum++].setPos(placedDice[i].getPosX(), placedDice[i].getPosY());
                                            diceTriggeredNum.m[ElementType::cai]++;
                                        }
                                    }
                                    else {
                                        vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
                                        sort(vec.begin(), vec.end(), Cost::cmp);
                                        for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
                                        {
                                            if (it->first != ElementType::cai) {
                                                n += it->second;
                                                if (n >= i) {
                                                    if (diceTriggeredNum.m[it->first] < triggeredCard->cost.m[it->first] + triggeredCard->cost.m[ElementType::cai]) {
                                                        diceTriggered[i] = true;
                                                        mGame->diceTriggerred[selectedDiceNum++].setPos(placedDice[i].getPosX(), placedDice[i].getPosY());
                                                        diceTriggeredNum.m[it->first]++;
                                                    }
                                                    break;
                                                }
                                            }
                                        }
                                    }


                                }
                                cout << "ʹ��card ��" << i << endl;
                                cout << "�Ѿ�ѡ�������" << endl;
                                for (auto i = diceTriggeredNum.m.begin(); i != diceTriggeredNum.m.end(); i++) {
                                    cout << (int)(*i).first << " " << (*i).second << endl;
                                }
                                break;
                            }
                        }
                    }
                }
                
                
            }
            
        }
        else if (isChangingRole)
        {
        Cost changingRoleCost(1, pair<ElementType, int>(ElementType::cai, 1));
        if (diceTriggeredNum >= changingRoleCost)  //���˵ķ��ã����ܲ�Ϊ1
        {
            if (mGame->changeConfirm.isIn(mPoint.x, mPoint.y))
            {
                selectedDiceNum = 0;
                mGame->diceNum = mGame->diceNum - diceTriggeredNum;
                diceTriggeredNum = Cost();
                for (int i = 0; i < mGame->diceNum.getSize(); i++)
                {
                    diceTriggered[i] = false;
                }
                for (int i = mGame->diceNum.getSize(); i < 8; i++)
                {
                    diceTriggered[i] = true;
                }
                isChanged = true;
                isConsumingDice = false;
            }
            else {
                CancelConsumingDice(mPoint);
            }
        }
        else {
            CancelConsumingDice(mPoint);
            for (int i = 0; i < mGame->diceNum.getSize(); i++)
            {
                if (placedDice[i].isIn(mPoint.x, mPoint.y)) {
                    if (diceTriggered[i]) {
                        diceTriggered[i] = 0;
                        int n = -1;
                        n += mGame->diceNum.m[ElementType::cai];
                        if (n >= i) {
                            diceTriggeredNum.m[ElementType::cai]--;
                        }
                        else {
                            vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
                            sort(vec.begin(), vec.end(), Cost::cmp);
                            for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
                            {
                                if (it->first != ElementType::cai) {
                                    n += it->second;
                                    if (n >= i) {
                                        diceTriggeredNum.m[it->first]--;
                                        break;
                                    }
                                }
                            }
                        }
                    }

                    else {
                        //ѡ������
                        int n = -1;
                        n += mGame->diceNum.m[ElementType::cai];
                        if (n >= i) {
                            if (!(diceTriggeredNum >= changingRoleCost)) {
                                diceTriggered[i] = true;
                                diceTriggeredNum.m[ElementType::cai]++;
                                mGame->diceTriggerred[selectedDiceNum++].setPos(placedDice[i].getPosX(), placedDice[i].getPosY());
                            }
                        }
                        else {
                            vector< pair<ElementType, int> > vec(mGame->diceNum.m.begin(), mGame->diceNum.m.end());
                            sort(vec.begin(), vec.end(), Cost::cmp);
                            for (vector< pair<ElementType, int> >::iterator it = vec.begin(); it != vec.end(); ++it)
                            {
                                if (it->first != ElementType::cai) {
                                    n += it->second;
                                    if (n >= i) {
                                        mGame->diceTriggerred[selectedDiceNum++].setPos(placedDice[i].getPosX(), placedDice[i].getPosY());
                                        if (diceTriggeredNum.m[it->first] < changingRoleCost.m[it->first] + changingRoleCost.m[ElementType::cai]) {
                                            diceTriggered[i] = true;
                                            diceTriggeredNum.m[it->first]++;
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    cout << "ʹ�û��� ��" << i << endl;
                    cout << "�Ѿ�ѡ�������2" << endl;
                    for (auto i = diceTriggeredNum.m.begin(); i != diceTriggeredNum.m.end(); i++) {
                        cout << (int)(*i).first << " " << (*i).second << endl;
                    }
                }
            }

        }
        }
        
    }
    if (Card* temp = mGame->cards.cardMouse(mPoint.x, mPoint.y))
    {
        if (!isAbilityTriggered&&!isChangingRole&&!isCardTriggered&&!isCardFinished)
        {
            isCardTriggered = true;
            triggeredCard = temp;
            isConsumingDice = true;
        }
        else if (!isAbilityTriggered &&! isChangingRole && !isCardFinished){  //Ҫ�л�
            if (temp != triggeredCard)
            {
                triggeredCard = temp;
            }
            else {
                //triggeredCard = NULL;
            }
        }
    }
    for (auto it = mGame->characterVector.begin(); it != mGame->characterVector.end(); it++) {
        if (!isCardTriggered && it->isIn(mPoint.x, mPoint.y) && currentRole!=&(*it))
        {
            isChangingRole = true;
            target = &(*it);
            isConsumingDice = true;
            isAbilityTriggered = false;
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
        if (!isChangingRole && !isConsumingDice && (*i)->isIn(mPoint.x, mPoint.y))
        {
            if (i == mGame->sAbility.end() - 1 &&currentRole->getNp()== currentRole->maxNp()||i!= mGame->sAbility.end() - 1)
            {
                isConsumingDice = true;
                triggeredAbility = &(**i);
                target = mGame->CurrentEnemy();   //��ȡ���ˣ����˶����޸���� 
                isAbilityTriggered = true;
            }
         
        }
    }
}
void PlayerTurnState::RightButtonDown(Vector2i mPoint)
{
    //isConsumingDice = !isConsumingDice;
}
