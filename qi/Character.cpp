#include "Character.h"

Character::Character(Texture& texture, int width, int height, float x, float y,Texture&tbg,Texture& thp,Texture&tnp,string name,int hp , int npNum ,EquipmentType equipmentType,ElementType elementType):Role(texture, width, height, x, y,tbg,equipmentType, elementType)
{
    tnp0.loadFromFile("source/texture/np0.png");
    tnp1.loadFromFile("source/texture/np1.png");
    this->name = name;
    this->hp = hp;
    this->npNum = npNum;
    sHp.setTexture(thp);
    sHp.scale((float)windowWidth*hpWidth / (float)thp.getSize().x,
        (float)windowHeight*hpHeight / (float)thp.getSize().y);
    for (int i = 0; i < npNum; i++)
    {
        Sprite s;
        s.setTexture(tnp);
        s.setScale((float)windowWidth * npWidth / (float)tnp.getSize().x,
            (float)windowHeight * npHeight / (float)tnp.getSize().y);
        sNp.push_back(s);
    }
    
}
Character::~Character() {}
void Character::draw(RenderWindow& window,float x,float y, Shader& shader)
{
    if (isDead)
    {
        shader.setUniform("brightness", -0.28f);
    }
    else {
        shader.setUniform("brightness", 0.0f);
    }    
    setScale(x, y);
    if (isFrozen)
    {
        shader.setUniform("blue", 0.6f);
    }
    else {
        shader.setUniform("blue", 0.0f);
    }

	Role::draw(window,shader);
    int times = 0;
    for (auto it = sNp.begin(); it != sNp.end(); it++) {
        it->setPosition(window.getSize().x * (this->x + npLeftOffset), window.getSize().y * (this->y + npUpOffset + npHeight*0.75 * (times++)));
        window.draw(*it);
    }
    sHp.setPosition(window.getSize().x * (this->x + hpLeftOffset), window.getSize().y * (this->y +hpUpOffset));
    window.draw(sHp);
    int count = 0;
    for (auto it = buffVector.begin(); it != buffVector.end(); it++)
    {
        it->setPos(this->x+0.005 + buffOffset * count++, this->y + cardHeight-0.037);
        it->draw(window);
    }
    Text text;
    text.setFont(font);
    text.setString(to_string(hp));

    if (hp < 10) {
        text.setPosition(window.getSize().x * (this->x + 0.15 * hpLeftOffset), window.getSize().y * (this->y + 0.15 * hpUpOffset));
    }
    else {
        text.setPosition(window.getSize().x * (this->x + 0.5 * hpLeftOffset), window.getSize().y * (this->y));
    }
    text.setCharacterSize(float(window.getSize().y) / float(windowHeight) * fontSize);
    text.setFillColor(Color::White);
    window.draw(text);

}
void Character::setScale(float x, float y)
{
    Role::setScale(x, y);
    //再设置血量和充能的scale
    sHp.setScale(x * (float)windowWidth * hpWidth / (float)sHp.getTexture()->getSize().x,
        y *(float)windowHeight * hpHeight / (float)sHp.getTexture()->getSize().y);
    for (auto it = sNp.begin(); it != sNp.end(); it++) {
        it->setScale(x*(float)windowWidth * npWidth / (float)it->getTexture()->getSize().x,
            y*(float)windowHeight * npHeight / (float)it->getTexture()->getSize().y);
    }
}

void Character::move()
{
    if (isDead)
    {
        y = characterY;
    }
    else
    {
        if (isSelected)
        {
            y = !isMoved ? y - moveOffset : y + moveOffset;
            isMoved = !isMoved;
        }
        else {
            if (isMoved)
            {
                y = y + moveOffset;
                isMoved = !isMoved;
            }
        }
    }
   
}

void Character::Selected(bool f)
{
    isSelected = f;
    move();   
}
bool Character::IsSelected()
{
    return isSelected;
}