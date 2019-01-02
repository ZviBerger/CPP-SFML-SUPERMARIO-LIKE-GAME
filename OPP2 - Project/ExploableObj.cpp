#include "ExploableObj.h"



ExploableObj::ExploableObj(sf::Vector2f & scaling, sf::FloatRect &fr)
	:RemovableObj(scaling,fr), m_hit(false), m_setedAnim(false)
{
	m_myBomb = std::make_unique<Bomb>(sf::Vector2f{ 1,1 },getPosition());
}

ExploableObj::~ExploableObj()
{
}

void ExploableObj::setIfHit(bool b)
{
	m_hit = b;
}

void ExploableObj::updateMove()
{
	
	if (!m_setedAnim)
	{
		m_myBomb->setPosition(getPosition());
		setAnim(m_myBomb->getAnim());
		m_setedAnim = true;
	}

	setLive(!m_myBomb->getAnim()->isEnd());
}


