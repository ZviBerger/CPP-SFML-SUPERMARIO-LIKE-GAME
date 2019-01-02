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
	using namespace sf;
	static sf::Color colors[] = { Color::Yellow, Color::Blue,
		Color::Cyan, Color::Magenta,Color::Red,Color::Black };
	return colors[rand() % 5];
}

