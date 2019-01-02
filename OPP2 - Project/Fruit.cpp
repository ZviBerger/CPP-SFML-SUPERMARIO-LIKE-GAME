#include "Fruit.h"



Fruit::Fruit(sf::Vector2f &scaling, sf::Vector2f& position)
	:RemovableObj(scaling, sf::FloatRect{ position.x,position.y,20,20 }), m_eated(false)

{
	static  sf::Texture txt{};
	static bool loaded = false;
	if (!loaded)
		loaded = txt.loadFromFile(path2image::fruit);
	setAnim(std::make_shared<Animation>(txt, 0, 0, 205, 205.333, 6, 0.09));
	m_myTextBox.settings("+100", sf::Vector2f{ 1,1 }, position);
	m_myTextBox.editCharSize(30);
	m_myTextBox.setPosition(sf::Vector2f{ position.x,position.y - 50 });

}


Fruit::~Fruit()
{
}

void Fruit::collide(GameObject & otherObject)
{
	otherObject.collide(*this);
}

void Fruit::collide(Astronaut & otherObject)
{
	astronautHitFruit(otherObject, *this);
}

void Fruit::draw(sf::RenderWindow & window)
{
	MovableObject::draw(window);
	if (m_eated) m_myTextBox.draw(window);
}

void Fruit::eated(const bool & eated)
{
	if (!eated)return;

	m_clock.restart();
	m_eated = eated;
}

bool Fruit::isEated() const
{
	return m_eated;
}

void Fruit::updateMove()
{
	if (!m_eated) return;

	auto s = m_clock.getElapsedTime().asMicroseconds() / 100000;
	setPosition(sf::Vector2f{ getPosition().x,getPosition().y - s*s });

	if (m_clock.getElapsedTime().asSeconds() > 5)
		setLive(false);
}
