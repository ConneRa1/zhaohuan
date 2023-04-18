#include "Enemy.h"
Enemy::Enemy(Texture& texture, int width, int height, float x, float y, Texture& tbg, Texture& thp, Texture& tnp, int hp, int npNum) :Role(texture, width, height, x, y, tbg)
{
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
void Enemy::Die()
{
    isDead = true;
}