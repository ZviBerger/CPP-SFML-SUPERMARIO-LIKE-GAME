#pragma once
#include "RemovableObj.h"
class Alien : public RemovableObj, public ProcessInterface
{
public:
	Alien(sf::Vector2f &scaling, sf::Vector2f& position);
	
	virtual void updateMove();
	virtual void draw(sf::RenderWindow & rw);
	virtual void collide(GameObject& otherObject);
	virtual void collide(Alien& otherObject) { ; }
	virtual void collide(Astroid& otherObject) { ; }
	virtual void collide(Astronaut& otherObject);
	virtual void collide(Bomb& otherObject) { ; }
	virtual void collide(Fruit& otherObject) { ; }
	virtual void collide(Rock& otherObject);
	virtual void collide(Shot& otherObject);
	virtual void collide(SpaceShip& otherObject) { ; }
	void setFallMode(bool f);
	bool getFallMode();
	void changeSide();
private:
	
	float m_dx,m_dy;
	bool m_go2right;
	bool m_falling;
	struct PhysicalValues m_phv;

};


