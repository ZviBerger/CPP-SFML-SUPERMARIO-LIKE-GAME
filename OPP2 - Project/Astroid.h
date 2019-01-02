#pragma once
#include "ExploableObj.h"
class ManageTrais;

class Astroid :public ExploableObj, public ProcessInterface
{
public:
	Astroid(sf::Vector2f &scaling, sf::Vector2f& position);
	virtual void updateMove();
	virtual void draw(sf::RenderWindow & window);
	virtual void collide(GameObject& otherObject);
	virtual void collide(Alien& otherObject);
	virtual void collide(Astroid& otherObject) { ; }
	virtual void collide(Astronaut& otherObject);
	virtual void collide(Bomb& otherObject) { ; }
	virtual void collide(Fruit& otherObject) { ; }
	virtual void collide(Rock& otherObject);
	virtual void collide(Shot& otherObject);
	virtual void collide(SpaceShip& otherObject) { ; }
private:
	float m_dx;
	float m_dy;
	
	
};
/////////////////////////////////////////////////////////////////////////
