#include "Astroid.h"
#include "ManageTrais.h"

 float time2live = 3;

Astroid::Astroid(sf::Vector2f &scaling, sf::Vector2f& position)
	:ExploableObj(scaling, sf::FloatRect{ position.x,position.y,20,20 })
{
	static  sf::Texture txt{};
	static bool loaded = false;
	if (!loaded) 
		loaded = txt.loadFromFile(path2image::astroid);
	auto animPtr = std::make_shared<Animation>(txt, 0, 0, 64, 64, 16, 0.5);
	animPtr->getSprite().rotate(float(rand() % 360));
	setAnim(animPtr);
	m_dx = float( rand() % 20-20 )/10.f;
	m_dy = float(rand() % 20 ) / 10.f;
}

void Astroid::updateMove()
{
	if (m_hit)
	{
		ExploableObj::updateMove();
		return;
	}
	ManageTrais::addSpark(getPosition(), 5, time2live);
	setPosition(getPosition() + V2f{ m_dx,m_dy });
}

void Astroid::draw(sf::RenderWindow & window)
{
	MovableObject::draw(window);
}

void Astroid::collide(GameObject & otherObject)
{
	otherObject.collide(*this);
}

void Astroid::collide(Alien & otherObject)
{
	astroidHitAlien(*this, otherObject);
}

void Astroid::collide(Astronaut & otherObject)
{
	astroidHitAstronout(*this, otherObject);
}

void Astroid::collide(Rock & otherObject)
{
	astroidHitRock(*this, otherObject);
}

void Astroid::collide(Shot & otherObject)
{
	astroidHitShot(*this, otherObject);
}


