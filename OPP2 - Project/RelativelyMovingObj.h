#pragma once
#include "RemovableObj.h"
class RelativelyMovingObj : public RemovableObj
{
public:
	RelativelyMovingObj(sf::Vector2f &scaling, sf::FloatRect & fr);
	virtual void collide(GameObject& otherObject) { ; }
	virtual void collide(Alien& otherObject) { ; }
	virtual void collide(Astroid& otherObject) { ; }
	virtual void collide(Astronaut& otherObject) { ; }
	virtual void collide(Bomb& otherObject) { ; }
	virtual void collide(Fruit& otherObject) { ; }
	virtual void collide(Rock& otherObject) { ; }
	virtual void collide(Shot& otherObject) { ; }
	virtual void collide(SpaceShip& otherObject) { ; }
	virtual void updateMove(const sf::Vector2f & relativePos)=0;
	virtual void updateMove() = 0;

	virtual ~RelativelyMovingObj() = 0;
};

