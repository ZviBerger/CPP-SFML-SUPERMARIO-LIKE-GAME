#include "Astronaut.h"
#include "TextBox.h"
#include<math.h>
#include "Fog.h"
//////////////////////////////////////////////////////////////
/// Constants section
/////////////////////////////////////////////////////////////
const float MaxAccel  = 6.f;
const float ZeroAccel = 0.f;
const float IncAccel = 0.1f;
const float DecAccel = 0.3f;

////////////////////////////////////////////////////////
// Astronaut C-tor
////////////////////////////////////////////////////////
Astronaut::Astronaut(sf::Vector2f &scaling, sf::Vector2f& position)
	:MovableObject(scaling, sf::FloatRect{ position.x,position.y,50, 110 }),
	m_jumping(false),
	m_falling(false),
	m_moving(false),
	m_falling2space(false),
	m_fruitNum(0),
	m_lifesNum(5),
	m_jumpCount(0),
	m_accel(0)
{
	static sf::Texture txt{};
	static bool loaded = false;
	if (!loaded)
		loaded = txt.loadFromFile(path2image::astronaut);
	
	m_go    = std::make_shared<Animation>(txt, 0, 256, 128, 128, 4, 0.3);
	m_jump  = std::make_shared<Animation>(txt, 256, 256, 128, 128, 2, 0.2);
	m_shoot = std::make_shared<Animation>(txt, 0, 0, 128, 128, 2, 0.8);
	m_hit   = std::make_shared<Animation>(txt, 0, 384, 128, 128, 1, 1);
	//I cen move anywhere
	m_cm2._down = m_cm2._up = m_cm2._right = m_cm2._left = true; 
	 
	//Set default animation
	m_animNow = m_go;
	setAnim(m_animNow);

	//My physics values
	m_phv._v0 = 8;
	m_phv._g = 12;   // 1.622;

	m_dx = position.x;
	m_dy = position.y;
	
}


Astronaut::~Astronaut()
{
}
////////////////////////////////////////////////////////
//  updateMove
////////////////////////////////////////////////////////
void Astronaut::updateMove()
{
	bool jumpBefor = m_jumping;
	float t = m_clock.getElapsedTime().asSeconds();
	float goUp   = m_phv._v0*t ;
	float goDown = m_cm2._down? 0.5f * m_phv._g * t*t : 0.f ; // y= v0*t- 1/2*g*t^2 

	m_jumping = (m_jumping &&  goUp >= goDown); //he is jumpimg or falling?

	if (m_jumping != jumpBefor)//recursive calling in case of he's on top of jumping path
		//otherwise there is a bit pic in he's movment
	{
		m_clock.restart();
		updateMove();
		return;
	}


	m_dy -=  ( m_jumping? goUp  : 0.f) - goDown ;
	m_dx += m_accel;
	setPosition(sf::Vector2f{ m_dx,m_dy });
	m_go->setSpeed(std::min( abs( m_accel) / 10, 0.3f));
	m_accel -= m_accel > 0 ? 0.03 : m_accel < 0 ? -0.03 : 0;
	m_accel = abs( m_accel) <= 0.03 ? 0 : m_accel;
	m_accel != 0 ? m_animNow->updateAnim() : [](){};

	m_falling2space = m_falling && m_clock.getElapsedTime().asSeconds() > 5;
}
////////////////////////////////////////////////////////
// draw
////////////////////////////////////////////////////////
void Astronaut::draw(sf::RenderWindow & window)
{

	if (!m_animNow) return;
	sf::FloatRect fl = getGlobalBounds();
	sf::Vector2f np{ fl.left + fl.width / 2 ,fl.top + fl.height / 2 };
	
	m_animNow->setPosition(np);
	window.draw(m_animNow->getSprite());
	



	/*///////////////////////////for debuging////////////////////////////////////
	TextBox tb{ std::to_string(m_accel),getPosition() };
	tb.draw(window);
	
	sf::FloatRect ast = getGlobalBounds();

	
	auto BL = sf::Vector2f{ ast.left +10 ,ast.top + ast.height-10 };
	auto BR = sf::Vector2f{ ast.left + ast.width-10 ,ast.top + ast.height -10};
	auto TR = sf::Vector2f{ ast.left + ast.width ,ast.top };
	auto TL = sf::Vector2f{ ast.left  ,ast.top };
	auto MR1 = sf::Vector2f{ ast.left + ast.width ,ast.top + ast.height / 2 + 20 };
	auto MR2 = sf::Vector2f{ ast.left + ast.width ,ast.top + ast.height / 2 };
	auto ML1 = sf::Vector2f{ ast.left ,ast.top + ast.height / 2 + 20 };
	auto ML2 = sf::Vector2f{ ast.left ,ast.top + ast.height / 2 };

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
	//*/


	
}
////////////////////////////////////////////////////////
//  setMove
////////////////////////////////////////////////////////
void Astronaut::setMove(Movments action, Movments key)
{
	m_moving = true; 
	m_accel = (m_accel > 0 && m_cm2._right) ? m_accel : (m_accel < 0 && m_cm2._left) ? m_accel :0 ;

	switch (action)
	{
	case Movments::GO:		
	{	
	if (key == RIGHT && m_cm2._right)
		m_accel += m_accel > MaxAccel ? 0: 00.1;
	else if (key == LEFT && m_cm2._left)
		m_accel -= m_accel < - MaxAccel ? 0 : 00.1;

	m_animNow = m_go;
	m_animNow->updateAnim();
	break;
	}
	case Movments::JUMP:
	{	
	if (!m_jumping && m_cm2._up && m_jumpCount <1)
	{
		m_jumpCount++;
		m_falling = true;
		m_jumping = true;
		m_clock.restart();
		m_animNow = m_jump;
	}
	break;
	}
	case Movments::SHOOT:
	{	
	m_animNow = m_shoot;
	m_animNow->updateAnim();
	break;
	}
	case Movments::STOP:
	{
		stop(key);
	break;
	}
	case Movments::MOVE:
	{	
	if (key == ALL)
	{
		m_cm2._down = m_cm2._up = m_cm2._right = m_cm2._left = true;
	}
	break;
	}
	case Movments::FALL:
	{	
	if (!m_falling && !m_jumping && m_cm2._down)
	{
		m_clock.restart();
		m_falling = true;
	}
	break;
	}
	default: {	}
		break;
	}
	if (key == LEFT)
	m_animNow->getSprite().setScale(sf::Vector2f{ -1.f,1.f });
	if (key == RIGHT)
	m_animNow->getSprite().setScale(sf::Vector2f{ 1.f,1.f });
}
////////////////////////////////////////////////////////
//  stop
////////////////////////////////////////////////////////
void Astronaut::stop(Movments forbidenDir)
{


	switch (forbidenDir)
	{
	case RIGHT:
	{
		m_cm2._right = false;
		break; 
	}
	case LEFT:
	{
		m_cm2._left = false;
		break;
	}
	case UP:
	{
		m_cm2._up = m_jumping = false;
		break;
	}
	case DOWN:
	{
		setStandAnim();
		m_cm2._down = false;
		m_jumpCount = 0;
		if (!m_jumping)
		{
			m_falling = false;
			m_clock.restart();
		}
		break; 
	}
		
	default:
		break;
	}
}

////////////////////////////////////////////////////////
// collide
////////////////////////////////////////////////////////
void Astronaut::collide(GameObject & otherObject)
{
	otherObject.collide(*this);
}

void Astronaut::collide(Alien & otherObject)
{
	astronautHitAlien(*this, otherObject);
}

void Astronaut::collide(Fruit & otherObject)
{
	astronautHitFruit(*this, otherObject);
}

void Astronaut::collide(Rock & otherObject)
{
	astronautHitRock(*this, otherObject);
}

void Astronaut::collide(SpaceShip & otherObject)
{
	astronautHitSpaceShip(*this, otherObject);
}

