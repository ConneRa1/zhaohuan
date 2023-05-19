#include "Role.h"
Role::Role() {}
Role::Role(Texture& texture, int width, int height, float x, float y, Texture& tbg,EquipmentType equipmentType,ElementType elementType) :Object(texture, width, height, x, y)
{
	bg.setTexture(tbg);
	bg.scale((float)width / (float)tbg.getSize().x,
		(float)height / (float)tbg.getSize().y);
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->equipmentType = equipmentType;
	this->elementType = elementType;
}
Role::~Role() {}

void Role::updateNp() {
	for (int i = 0; i < sNp.size(); i++)
	{
		if (i + 1 <= currentNp)
		{
			sNp[i].setTexture(tnp1);
		}
		else {
			sNp[i].setTexture(tnp0);
		}

	}
}

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
void Role::getHurt(Role* role,int x,bool isDaZhao)
{
	vector<int> erease;
	for (auto it = 0; it < role->buffVector.size(); it++)
	{
		if ((role->buffVector[it].type == BuffType::º”π•|| role->buffVector[it].type == BuffType::Œ‰∆˜ )&&!isDaZhao)
		{
			x += role->buffVector[it].num;
			role->buffVector[it].times -= 1;
			if (role->buffVector[it].times <= 0)
			{
				erease.push_back(it);
			}
		}
		else if (isDaZhao && role->buffVector[it].type == BuffType::¥Û’–)
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
		if (buffVector[it].type == BuffType::∂‹)
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
	cout << " £”‡—™¡ø£∫" << hp << endl;
}
void Role::getHurt(Role* role, int x)
{
	vector<int> erease;
	for (auto it = 0; it < role->buffVector.size(); it++)
	{
		if (role->buffVector[it].type == BuffType::º”π• || role->buffVector[it].type == BuffType::Œ‰∆˜)
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
		if (buffVector[it].type == BuffType::∂‹)
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
	cout << " £”‡—™¡ø£∫" << hp << endl;
}

int Role::getHurtNum()
{
	
	return hurtNum;
}

void Role::getHurt( int x)
{
	hp -= x;
	cout << " £”‡—™¡ø£∫" << hp << endl;
}
void Role::deleteBuff(BuffType type) 
{
	for (auto it = 0; it < buffVector.size(); it++)
	{
		if (buffVector[it].type == BuffType::±•)
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

void Role::move(bool isplayer)
{
	if (isplayer)
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
					isMoved = false;
				}
			}
		}
	}
	else {
		if (isDead)
		{
			y = enemyY;
		}
		else
		{
			if (isSelected)
			{
				y = !isMoved ? y + moveOffset : y;
				isMoved = !isMoved;
			}
			else {
				if (isMoved)
				{
					y = y - moveOffset;
					isMoved = false;
				}
			}
		}
	}
	

}

void Role::Selected(bool f,bool isplayer)
{
	isSelected = f;
	move(isplayer);
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
			return ReactType::∂≥Ω·;
			break;
		case ElementType::lei:
			attachedElement = ElementType::cai;
			return ReactType::∏–µÁ;
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
			return ReactType::∂≥Ω·;
			break;
		case ElementType::lei:
			attachedElement = ElementType::cai;
			return ReactType::≥¨µº;
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
			return ReactType::≥¨µº;
			break;
		case ElementType::shui:
			attachedElement = ElementType::cai;
			return ReactType::∏–µÁ;
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

EquipmentType Role:: getEquipmentType() const{
	return this->equipmentType;
}
ElementType Role::getElementType() const {
	return this->elementType;
}

void Role::addEquipment(Buff buff) {

	for (auto it = buffVector.begin(); it != buffVector.end(); it++) {
		if ((*it).type == BuffType::Œ‰∆˜) {
			(*it) = buff;
			return;
		}	
	}
	buffVector.push_back(buff);
	return;
}

void Role::addRelic(Buff buff) {

	for (auto it = buffVector.begin(); it != buffVector.end(); it++) {
		if ((*it).type == BuffType:: •“≈ŒÔ) {
			(*it) = buff;
			return;
		}
	}
	buffVector.push_back(buff);
	return;
}

bool Role::haveRelic() {
	for (auto it = buffVector.begin(); it != buffVector.end(); it++) {
		if ((*it).type == BuffType:: •“≈ŒÔ) {
			return 1;
		}
	}
	return 0;
}