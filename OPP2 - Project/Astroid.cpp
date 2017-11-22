#include "Astroid.h"



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
	m_dx = rand() % 2-2;
	m_dy = rand() % 3;
}

void Astroid::updateMove()
{
	if (m_hit)
	{
		ExploableObj::updateMove();
		return;
	}
	setPosition(sf::Vector2f{ getPosition().x + m_dx,getPosition().y + m_dy });
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


