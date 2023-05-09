#include "Role.h"
Role::Role() {}
Role::Role(Texture& texture, int width, int height, float x, float y, Texture& tbg) :Object(texture, width, height, x, y)
{
	bg.setTexture(tbg);
	bg.scale((float)width / (float)tbg.getSize().x,
		(float)height / (float)tbg.getSize().y);
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

}
Role::~Role() {}
void Role::draw(RenderWindow& window)
{
	Object::draw(window);
	bg.setPosition(window.getSize().x * x, window.getSize().y * y);
	window.draw(bg);
	

}
void Role::draw(RenderWindow& window,Shader &shader)
{
	Object::draw(window,shader);
	bg.setPosition(window.getSize().x * x, window.getSize().y * y);
	window.draw(bg);
}
void Role::setScale(float x,float y)
{
	Object::setScale(x,y);
	bg.setScale(x * float(sprite.getTexture()->getSize().x) / float(bg.getTexture()->getSize().x), y*float(sprite.getTexture()->getSize().y) / float(bg.getTexture()->getSize().y));
}
void Role::getHurt(Role* role,int x)
{
	vector<int> erease;
	for (auto it = 0; it < role->buffVector.size(); it++)
	{
		if (role->buffVector[it].type == BuffType::加攻)
		{
			x += role->buffVector[it].num;
			role->buffVector[it].times -= 1;
			if (role->buffVector[it].times <= 0)
			{
				erease.push_back(it);
			}
		}
	}
	for (auto it = 0; it < erease.size(); it++)
	{
		role->buffVector.erase(role->buffVector.begin() + erease[it]);
	}
	erease.clear();
	
	
	for (auto it = 0; it < buffVector.size(); it++)
	{
		if (buffVector[it].type == BuffType::盾)
		{
			x -= buffVector[it].num;
			buffVector[it].times -= 1;
			if (buffVector[it].times <= 0)
			{
				erease.push_back(it);
			}
		}
	}
	for (auto it = 0; it < erease.size(); it++)
	{
		buffVector.erase(buffVector.begin() + erease[it]);
	}
	erease.clear();
	hp -= x;
	hurtNum = x;
	cout << "剩余血量：" << hp << endl;
}

int Role::getHurtNum()
{
	
	return hurtNum;
}

void Role::getHurt( int x)
{
	hp -= x;
	cout << "剩余血量：" << hp << endl;
}
void Role::deleteBuff(BuffType type) 
{
	for (auto it = 0; it < buffVector.size(); it++)
	{
		if (buffVector[it].type == BuffType::饱)
		{
			buffVector.erase(buffVector.begin() + it);
			break;
		}
	}

}
bool Role::checkReact(ElementType e) 
{
	if (attachedElement == ElementType::cai || attachedElement == e)
	{
		attachedElement = e;
		return false;
	}
	else if (e == ElementType::cai)
	{
		return false;
	}
	else {
		return true;
	}
	
}
ReactType Role::doReact(ElementType e) 
{
	switch (attachedElement)
	{
	case ElementType::shui:
		switch (e)
		{
		case ElementType::bing:
			attachedElement = ElementType::cai;
			return ReactType::冻结;
			break;
		case ElementType::lei:
			attachedElement = ElementType::cai;
			return ReactType::感电;
			break;
		default:
			break;
		}
		break;
	case ElementType::bing:
		switch (e)
		{
		case ElementType::shui:
			attachedElement = ElementType::cai;
			return ReactType::冻结;
			break;
		case ElementType::lei:
			attachedElement = ElementType::cai;
			return ReactType::超导;
			break;
		default:
			break;
		}
		break;
	case ElementType::lei:
		switch (e)
		{
		case ElementType::bing:
			attachedElement = ElementType::cai;
			return ReactType::超导;
			break;
		case ElementType::shui:
			attachedElement = ElementType::cai;
			return ReactType::感电;
			break;
		default:
			break;
		}
		break;
	case ElementType::cao:
		break;
	case ElementType::yan:
		break;
	case ElementType::huo:
		break;
	case ElementType::feng:
		break;
	default:
		break;
	}

}