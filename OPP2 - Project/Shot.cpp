#include "Shot.h"



Shot::Shot(sf::Vector2f & scaling, sf::Vector2f & position)
	:ExploableObj(scaling, sf::FloatRect{ position.x,position.y,10,20 }){
	Shot::Shot(scaling, position, RIGHT);

}

Shot::Shot(sf::Vector2f &scaling, sf::Vector2f& position,Movments side)
	:ExploableObj(scaling, sf::FloatRect{ position.x,position.y,10,20 })
	,ProcessInterface(), m_sideOfShot(side)
{
	static  sf::Texture txt{};
	static bool loaded = false;
	if(!loaded)
		loaded = txt.loadFromFile(path2image::shot);

	m_clock.restart();
	auto anim = std::make_shared<Animation>(txt, 0, 0, 32, 64, 16, 0.8);
	anim->getSprite().rotate(90);
	setScaling((m_sideOfShot == LEFT) ? V2f{  scaling.x,-1*scaling.y } : scaling);	
	setAnim(anim);
	
	m_phv._angel = 0.f;
	m_phv._g = 1.62f;
	m_phv._v0 = 15.f;
}

void Shot::updateMove()
{
	if (m_hit)
	{
		ExploableObj::updateMove();
		return;   
     }
	float t = m_clock.getElapsedTime().asSeconds(); 
	if (t > 3)
	{
		setLive(false);
		return;
	}
	float x = m_phv._v0*cos(m_phv._angel)*t;                     //x = V0*cos(A)*t
	float y =  m_phv._v0*sin(m_phv._angel)*t - 0.5f*m_phv._g*t*t; //y = V0*sin(A)*t-0.5*g*t^2  
	x = (m_sideOfShot == LEFT) ? -x : x;
	setPosition(sf::Vector2f{getPosition().x + x,getPosition().y  -  y });
}


void Shot::collide(GameObject & otherObject)
{
	otherObject.collide(*this);
}


void Shot::setSide(Movments side2move)
{
	if (side2move != RIGHT && side2move != LEFT)
		return;

		m_sideOfShot = side2move;
}

