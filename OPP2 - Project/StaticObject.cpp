#include "StaticObject.h"



StaticObject::StaticObject(sf::Vector2f &scaling, sf::FloatRect &fr)
	:GameObject(scaling,fr)
{
	m_sprite.setScale(scaling);
	m_sprite.setPosition(getPosition());
}


StaticObject::~StaticObject()
{
}

void StaticObject::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

bool StaticObject::collideWithMe(const sf::FloatRect & other)
{
	return getGlobalBounds().intersects(other);
}

void StaticObject::setSpriteTexture(sf::Texture & txt)
{
	m_sprite.setTexture(txt);
}

void StaticObject::setTextureRect(sf::IntRect & iR)
{
	m_sprite.setTextureRect(iR);
}

sf::Sprite & StaticObject::getSprite()
{
	return m_sprite;
}
