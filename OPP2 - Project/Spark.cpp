#include "Spark.h"
#include "TextBox.h"



Spark::Spark( V2f & position, float zIndex,float time2live)
	:RelativelyMovingObj{ V2f{},sf::FloatRect{} },
	m_dz(zIndex),
	m_time2live(time2live)
	
{

	static  sf::Texture txt{}; //same texture for any spark
	static bool loaded = false;
	if (!loaded)
		loaded = txt.loadFromFile(path2image::spark);

	m_cs.setTexture(txt);

	m_dz /= 10;
	m_dz += 0.5;
	m_dx = float(rand()%(rand() %3 +1))/5 + m_dz;
	m_dx = (rand() % 2 == 0 ? m_dx : -m_dx)/10;
	m_dy = float(rand() % (rand() %3 +1))/5 + m_dz;
	m_dy = (rand() % 2 == 0 ? m_dy : -m_dy)/10;
	m_clock.restart();
	//m_cs.setFillColor(sf::Color::White);
	setPosition(position);
	m_cs.setPosition(position);
	//m_cs.setRadius(m_dz);
	m_cs.setScale(V2f{ m_dz*0.045f ,m_dz*0.045f });
	m_movingFactor = m_dz >= 1 ? V2f{ m_dz, m_dz } : V2f{ 1 / m_dz,1 / m_dz };

}


Spark::~Spark()
{
}



void Spark::updateMove()
{
	setLive(m_clock.getElapsedTime().asSeconds() < m_time2live);
	setPosition(V2f{ m_dx  + getPosition().x ,getPosition().y + m_dy });
	m_cs.setPosition(getPosition());
}



void Spark::draw(sf::RenderWindow & window)
{
	window.draw(m_cs);
	
}

void Spark::updateMove(const sf::Vector2f &movePos)
{
	setLive(!(m_clock.getElapsedTime().asSeconds() > m_time2live));
	setPosition( getPosition() + V2f{ m_dx,m_dy });
	m_cs.setPosition(V2f{ movePos - getPosition() }/ m_movingFactor + V2f{ 1200 ,500 });

}

void Spark::setColor(sf::Color  c)
{
	m_cs.setColor(c);
	
}
