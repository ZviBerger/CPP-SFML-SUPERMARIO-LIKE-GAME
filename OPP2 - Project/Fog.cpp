#include "Fog.h"
#include "TextBox.h"
static TextBox tb{ "#", V2f{1,1,} };

Fog::Fog(sf::Vector2f &scaling, sf::Vector2f& position)
	:RelativelyMovingObj(scaling, sf::FloatRect{ 0,0,0,0 })
	, m_initPos(position)
{
	static sf::Texture txt{};
	static bool loaded = false;
	if (!loaded)
		loaded = txt.loadFromFile(path2image::fog);
	
	auto animPtr = std::make_shared<Animation>(txt, 0, 0, 850, 365, 1, 0);
	//animPtr->getSprite().setColor(sf::Color::Cyan);
	setAnim(animPtr);
	setPosition(position + V2f{ 1000,0 });
	
	m_dx =  float(rand() % 40 -20)/10 ;
	m_dy = 0;// float(rand() % 30 - 15);

	m_dz = scaling.x/100;
	
	setScaling( V2f{ 1.f ,1.f } );
	m_movingFactor = m_dz >= 1 ? V2f{ m_dz, m_dz } : V2f{ 1/ m_dz,1 / m_dz };
}

void Fog::updateMove()
{
	setPosition(getPosition() + V2f{ m_dx,m_dy });
}


void Fog::updateMove(const sf::Vector2f &movePos)
{
	auto oldPos = getPosition();
	//oldPos.x = oldPos.x + (movePos.x - oldPos.x )/100;
	
	setPosition(oldPos + V2f{ m_dx,m_dy });// +V2f{ V2f{movePos - oldPos  } / m_movingFactor } +V2f{ 600,300 });
	

}

void Fog::draw(sf::RenderWindow & window)
{
	RelativelyMovingObj::draw(window);
	tb.settings("pos:"+std::to_string(int(getPosition().x)) + "," + std::to_string(int(getPosition().y))
	+"\nspeed:" + std::to_string(m_dx) + "," + std::to_string(m_dy)
		, V2f{ 1,1 }, getPosition());
	//tb.draw(window);
}
