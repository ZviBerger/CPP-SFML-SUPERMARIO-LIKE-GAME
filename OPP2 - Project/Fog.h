#pragma once
#include "RelativelyMovingObj.h"
class Fog : public RelativelyMovingObj
{
public:
	Fog(sf::Vector2f &scaling, sf::Vector2f& position);
	
	virtual void collide(GameObject& otherObject) { ; }
	virtual void collide(Alien& otherObject) { ; }
	virtual void collide(Astroid& otherObject) { ; }
	virtual void collide(Astronaut& otherObject) { ; }
	virtual void collide(Bomb& otherObject) { ; }
	virtual void collide(Fruit& otherObject) { ; }
	virtual void collide(Rock& otherObject) { ; }
	virtual void collide(Shot& otherObject) { ; }
	virtual void collide(SpaceShip& otherObject) { ; }
	virtual void updateMove();
	virtual void updateMove(const sf::Vector2f &movePos); //updating movment relatively to position and the Z axe
	virtual void draw(sf::RenderWindow & window);
private:
	float m_dx, m_dy, m_dz;
	V2f m_movingFactor, m_initPos;
};
