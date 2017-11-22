#include "SpaceShip.h"






SpaceShip::SpaceShip(sf::Vector2f & scaling, sf::Vector2f & position)
	:RemovableObj(scaling, sf::FloatRect{ position.x,position.y,500,500 }),m_astroInside(false)
{
	static  sf::Texture txt{};
	static sf::Texture m_rocketTxt;
	static bool loaded = false;
	if (!loaded)
		loaded = txt.loadFromFile(path2image::spaceShip);
	 setAnim(std::make_shared<Animation>(txt, 0, 0, 720, 713, 1, 0));


	m_rocketTxt.loadFromFile(path2image::rocketFire);
	m_r1 = std::make_unique<Animation>(m_rocketTxt, 0, 0, 32, 64, 16, 0.8);
	m_r2 = std::make_unique<Animation>(m_rocketTxt, 0, 0, 32, 64, 16, 0.8);
	m_r1->setPosition(sf::Vector2f{ position.x+110,position.y + 525 });
	m_r2->setPosition(sf::Vector2f{ position.x + 390,position.y + 525 });
	m_r1->getSprite().setScale(sf::Vector2f{ 3,3 });
	m_r2->getSprite().setScale(sf::Vector2f{ 3,3 });
}


SpaceShip::~SpaceShip()
{
}

void SpaceShip::collide(GameObject & otherObject)
{
	otherObject.collide(*this);
}

void SpaceShip::collide(Astronaut & otherObject)
{
	astronautHitSpaceShip(otherObject, *this);
}

void SpaceShip::draw(sf::RenderWindow & window)
{
	m_r1->updateAnim();
	m_r2->updateAnim();
	MovableObject::draw(window);
	window.draw(m_r1->getSprite());
	window.draw(m_r2->getSprite());
}

void SpaceShip::updateMove()
{
	if (!m_astroInside) return;

	setPosition(sf::Vector2f{ getPosition().x,getPosition().y - 2 });
	m_r1->setPosition(sf::Vector2f{ m_r1->getPosition().x,m_r1->getPosition().y - 2 });
	m_r2->setPosition(sf::Vector2f{ m_r2->getPosition().x,m_r2->getPosition().y - 2 });
}

void SpaceShip::setAstroInside(bool c)
{
	m_astroInside = c;
}

bool SpaceShip::isAstroInside() const
{
	return m_astroInside;
}




