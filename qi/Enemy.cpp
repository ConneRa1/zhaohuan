#include "Enemy.h"
Enemy::Enemy(Texture& texture, int width, int height, float x, float y, Texture& tbg, Texture& thp, Texture& tnp, int hp, int npNum) :Role(texture, width, height, x, y, tbg)
{
    this->hp = hp;
    this->npNum = npNum;
    sHp.setTexture(thp);
    sHp.scale((float)windowWidth * hpWidth / (float)thp.getSize().x,
        (float)windowHeight * hpHeight / (float)thp.getSize().y);
    for (int i = 0; i < npNum; i++)
    {
        Sprite s;
        s.setTexture(tnp);
        s.setScale((float)windowWidth * npWidth / (float)tnp.getSize().x,
            (float)windowHeight * npHeight / (float)tnp.getSize().y);
        sNp.push_back(s);
    }
}
Enemy::~Enemy() {}

void Enemy::draw(RenderWindow& window, float x, float y, Shader& shader)
{
    if (isDead)
    {
        shader.setUniform("brightness", -0.25f);
    }
    else {
        shader.setUniform("brightness", 0.0f);
    }
    setScale(x, y);
    Role::draw(window,shader);
    int times = 0;
    for (auto it = sNp.begin(); it != sNp.end(); it++) {
        it->setPosition(window.getSize().x * (this->x + npLeftOffset), window.getSize().y * (this->y + npUpOffset + npHeight * 0.75 * (times++)));
        window.draw(*it);
    }
    sHp.setPosition(window.getSize().x * (this->x + hpLeftOffset), window.getSize().y * (this->y + hpUpOffset));
    window.draw(sHp);

    Text text;
    text.setFont(font);
    text.setString(to_string(hp));
    
    if (hp < 10) {
        text.setPosition(window.getSize().x * (this->x+0.15* hpLeftOffset), window.getSize().y * (this->y+0.15* hpUpOffset));
    }
    else {
        text.setPosition(window.getSize().x * (this->x+ 0.5*hpLeftOffset), window.getSize().y * (this->y));
    }
    text.setCharacterSize(float(window.getSize().y)/float(windowHeight)*fontSize);
    text.setFillColor(Color::White);
    window.draw(text);

}
void Enemy::setScale(float x, float y)
{
    Role::setScale(x, y);
    //再设置血量和充能的scale
    sHp.setScale(x * (float)windowWidth * hpWidth / (float)sHp.getTexture()->getSize().x,
        y * (float)windowHeight * hpHeight / (float)sHp.getTexture()->getSize().y);
    for (auto it = sNp.begin(); it != sNp.end(); it++) {
        it->setScale(x * (float)windowWidth * npWidth / (float)it->getTexture()->getSize().x,
            y * (float)windowHeight * npHeight / (float)it->getTexture()->getSize().y);
    }

}
void Enemy::move()
{
    y =!isMoved ?y+moveOffset:y-moveOffset;
    isMoved = !isMoved;
}
