#include "SpaceShip.h"
#include "ManageTrais.h"





SpaceShip::SpaceShip(sf::Vector2f & scaling, sf::Vector2f & position)
	:RemovableObj(scaling, sf::FloatRect{ position.x,position.y,500,500 })
	,m_astroInside(false),m_init(false)
{
	static  sf::Texture txt{};
	static sf::Texture m_rocketTxt;
	static bool loaded = false;
	if (!loaded)
		loaded = txt.loadFromFile(path2image::spaceShip);
	 setAnim(std::make_shared<Animation>(txt, 0, 0, 720, 713, 1, 0));

	m_rocketTxt.loadFromFile(path2image::rocketFire);
	m_leftRocket = std::make_unique<Animation>(m_rocketTxt, 0, 0, 32, 64, 16, 0.8);
	m_rightRocket = std::make_unique<Animation>(m_rocketTxt, 0, 0, 32, 64, 16, 0.8);
	m_leftRocket->setPosition(sf::Vector2f{ position.x+110,position.y + 525 });
	m_rightRocket->setPosition(sf::Vector2f{ position.x + 390,position.y + 525 });
	m_leftRocket->getSprite().setScale(sf::Vector2f{ 3,3 });
	m_rightRocket->getSprite().setScale(sf::Vector2f{ 3,3 });
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
	m_leftRocket->updateAnim();
	m_rightRocket->updateAnim();
	MovableObject::draw(window);
	if (m_astroInside) {
		window.draw(m_leftRocket->getSprite());
		window.draw(m_rightRocket->getSprite());
	}
}

void SpaceShip::updateMove()
{
	if (!m_astroInside) return;
	if (!m_init) {
		m_clock.restart();
		m_init = true;
	}
	float t = m_clock.getElapsedTime().asSeconds();
	setPosition( getPosition() - V2f{0, t*t });
	m_leftRocket->setPosition( m_leftRocket->getPosition() - V2f{0, t*t });
	m_rightRocket->setPosition( m_rightRocket->getPosition()- V2f{0, t*t });
	for (int i = 0; i < 10; i++) {
		ManageTrais::addSpark(m_leftRocket->getPosition(), rand() % 15+5, 8.0f);
		ManageTrais::addSpark(m_rightRocket->getPosition(), rand() % 15+5, 8.0f);
	}

}

void SpaceShip::setAstroInside(bool c)
{
	m_astroInside = c;
}

bool SpaceShip::isAstroInside() const
{
	return m_astroInside;
}




