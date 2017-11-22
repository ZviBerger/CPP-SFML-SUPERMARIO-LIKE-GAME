#pragma once
#include "ExploableObj.h"
class Shot : public ExploableObj, public ProcessInterface
{
public:
	Shot(sf::Vector2f &scaling, sf::Vector2f& position);
	Shot(sf::Vector2f &scaling, sf::Vector2f& position, Movments side);
	virtual void updateMove();
	virtual void collide(GameObject& otherObject);
	virtual void collide(Alien& otherObject) { ; }
	virtual void collide(Astroid& otherObject) { ; }
	virtual void collide(Astronaut& otherObject) { ; }
	virtual void collide(Bomb& otherObject) { ; }
	virtual void collide(Fruit& otherObject) { ; }
	virtual void collide(Rock& otherObject) { ; }
	virtual void collide(Shot& otherObject) { ; }
	virtual void collide(SpaceShip& otherObject) { ; }
	void setSide(Movments side2move);
private:
	struct PhysicalValues m_phv;
	Movments m_sideOfShot;
	
};

