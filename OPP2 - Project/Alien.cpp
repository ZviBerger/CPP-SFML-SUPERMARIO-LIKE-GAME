#include "Alien.h"

/////////////////////////////////////////////////////////////////////////////////////
//Alien C-tor
/////////////////////////////////////////////////////////////////////////////////////
Alien::Alien(sf::Vector2f &scaling, sf::Vector2f& position)
	: RemovableObj(scaling, sf::FloatRect{ position.x,position.y,30,100 })
	,m_dx(2), m_go2right(true),m_falling(false)
{
	static  sf::Texture txt{};
	static bool loaded = false;
	if (!loaded)
		loaded = txt.loadFromFile(path2image::alien);
	setAnim(std::make_shared<Animation>(txt, 0, 0, 833.75f, 921.f, 4, 0.15f));
	//My physics values
	m_phv._g =14;   // 1.622;
	m_phv._angel = 0.5;
	m_dx  = 1.5;

	
}
/////////////////////////////////////////////////////////////////////////////////////
//updateMove
/////////////////////////////////////////////////////////////////////////////////////
void Alien::updateMove()
{
	auto t = m_clock.getElapsedTime().asSeconds();
	
	auto newPos = sf::Vector2f{ getPosition().x - m_dx, getPosition().y };
	if (!m_falling &&int(t) % 2 == 0)
	{
		m_falling = true;
		m_clock.restart();
		t = m_clock.getElapsedTime().asSeconds();
	}

	 if (m_falling) newPos.y+= 0.5f * m_phv._g * t*t;
	
	 setPosition(newPos);
}



void Alien::draw(sf::RenderWindow & window)
{
	MovableObject::draw(window);

	/*sf::FloatRect al = getGlobalBounds();
	auto BL = sf::Vector2f{ al.left  ,al.top + al.height };
	auto BR = sf::Vector2f{ al.left + al.width ,al.top + al.height };
	auto TR = sf::Vector2f{ al.left + al.width ,al.top };
	auto TL = sf::Vector2f{ al.left  ,al.top };
	auto MR1 = sf::Vector2f{ al.left + al.width ,al.top + al.height / 2 };
	auto MR2 = sf::Vector2f{ al.left + al.width ,al.top + al.height / 2 };
	auto ML1 = sf::Vector2f{ al.left ,al.top + al.height / 2  };
	auto ML2 = sf::Vector2f{ al.left ,al.top + al.height / 2 };

	sf::CircleShape bl{ 5 }, br{ 5 }, tr{ 5 }, tl{ 5 }, mr1{ 5 }, mr2{ 5 }, ml1{ 5 }, ml2{ 5 };

	bl.setFillColor(sf::Color::Blue);
	br.setFillColor(sf::Color::Blue);
	tr.setFillColor(sf::Color::Blue);
	tl.setFillColor(sf::Color::Blue);
	mr1.setFillColor(sf::Color::Blue);
	mr2.setFillColor(sf::Color::Blue);
	ml1.setFillColor(sf::Color::Blue);
	ml2.setFillColor(sf::Color::Blue);

	bl.setPosition(BL);
	br.setPosition(BR);
	tr.setPosition(TL);
	tl.setPosition(TR);
	mr1.setPosition(MR1);
	mr2.setPosition(MR2);
	ml1.setPosition(ML1);
	ml2.setPosition(ML2);

	window.draw(bl);
	window.draw(br);
	window.draw(tl);
	window.draw(tr);
	window.draw(mr1);
	window.draw(mr2);
	window.draw(ml1);
	window.draw(ml2);
	*/
}
/////////////////////////////////////////////////////////////////////////////////////
//collids:
/////////////////////////////////////////////////////////////////////////////////////
void Alien::collide(GameObject & otherObject)
{
	otherObject.collide(*this);
}

void Alien::collide(Astronaut & otherObject)
{
	astronautHitAlien(otherObject, *this);
}

void Alien::collide(Rock & otherObject)
{
	alienHitRock(*this, otherObject);
}
void Alien::collide(Shot & otherObject)
{
	alienHitShot(*this, otherObject);
}
/////////////////////////////////////////////////////////////////////////////////////
// setMoveMode
/////////////////////////////////////////////////////////////////////////////////////
void Alien::setFallMode(bool f)
{
	if (m_falling != f)
		m_clock.restart();

	m_falling = f;
}



bool Alien::getFallMode()
{
	return m_falling;
}
/////////////////////////////////////////////////////////////////////////////////////
//changeSide()
/////////////////////////////////////////////////////////////////////////////////////
void Alien::changeSide()
{
	setScaling(V2f{ getScale().x*-1.f,getScale().y });
	m_dx *= -1;
}




