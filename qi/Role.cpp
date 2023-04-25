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
void Role::getHurt(int x)
{
	hp -= x;
	cout << "ʣ��Ѫ����" << hp << endl;
}


bool Role::checkReact(ElementType e) 
{
	if (attachedElement == ElementType::cai || attachedElement == e)
	{
		attachedElement = e;
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
			return ReactType::����;
			break;
		case ElementType::lei:
			attachedElement = ElementType::cai;
			return ReactType::�е�;
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
			return ReactType::����;
			break;
		case ElementType::lei:
			attachedElement = ElementType::cai;
			return ReactType::����;
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
			return ReactType::����;
			break;
		case ElementType::shui:
			attachedElement = ElementType::cai;
			return ReactType::�е�;
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