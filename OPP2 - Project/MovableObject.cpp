#include "MovableObject.h"



MovableObject::MovableObject(sf::Vector2f &scaling, sf::FloatRect &fr)
	:GameObject(scaling,fr)
{}

void MovableObject::draw(sf::RenderWindow & window)
{
	if (!m_objAnimPtr) return;
     	m_objAnimPtr->getSprite().setScale(getScale());
		m_objAnimPtr->updateAnim();
		
		sf::FloatRect fl = getGlobalBounds();
		sf::Vector2f np{ fl.left + fl.width / 2,fl.top + fl.height / 2 };

		m_objAnimPtr->setPosition(np);
		window.draw(m_objAnimPtr->getSprite());
		
}

void MovableObject::setAnim(std::shared_ptr<Animation>& anim)
{
	m_objAnimPtr = anim;
}

void MovableObject::go2(sf::Vector2f & location)
{
	setPosition(location);
}

bool MovableObject::collideWithMe(const sf::FloatRect & other)
{
	return getGlobalBounds().intersects(other);
}


std::shared_ptr<Animation> MovableObject::getAnim()
{
	return m_objAnimPtr;
}


