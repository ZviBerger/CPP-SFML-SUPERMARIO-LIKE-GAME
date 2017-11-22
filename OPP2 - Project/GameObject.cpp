#include "GameObject.h"

GameObject::GameObject(sf::Vector2f & scaling, sf::FloatRect &fr)
	:m_scaling(scaling),m_myFloatRect(fr),m_alive(true),m_born(false)
{
	
}

sf::Vector2f GameObject::getPosition() 
{
	return sf::Vector2f{ m_myFloatRect.left,m_myFloatRect.top };
}

sf::FloatRect GameObject::getGlobalBounds()
{
	return m_myFloatRect;
}

void GameObject::setPosition(sf::Vector2f & toMove)
{
	m_myFloatRect.left = toMove.x ;
	m_myFloatRect.top = toMove.y ;
}

void GameObject::setScaling(sf::Vector2f & scaling)
{
	m_scaling = scaling;
}

sf::Vector2f GameObject::getScale() const
{
	return m_scaling;
}

bool GameObject::isAlive() const
{
	return m_alive;
}

void GameObject::setLive(bool b)
{
	m_alive = b;
}

void GameObject::setWasBorn(bool birth)
{
	m_born = birth;
}

bool GameObject::wasBorn()
{
	return m_born;
}

bool GameObject::contains(sf::Vector2f & point)
{
	return m_myFloatRect.contains(point);
}

sf::Color GameObject::getRandomColor() const
{

	switch (rand() % 7)
	{
	case 0:
		return sf::Color::Yellow;
	case 1:
		return sf::Color::Blue;
	case 2:
		return sf::Color::Cyan;
	case 3:
		return sf::Color::Green;
	case 4:
		return sf::Color::Magenta;
	case 5:
		return sf::Color::Red;
	case 6:
		return sf::Color::Black;

	default:
		break;
	}

	return sf::Color();
}

