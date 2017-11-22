#pragma once
#include "RemovableObj.h"
class SpaceShip :public RemovableObj, public ProcessInterface
{
public:
	SpaceShip(sf::Vector2f &scaling, sf::Vector2f& position);
	~SpaceShip();
	virtual void collide(GameObject& otherObject);
	virtual void collide(Alien& otherObject) { ; }
	virtual void collide(Astroid& otherObject) { ; }
	virtual void collide(Astronaut& otherObject);
	virtual void collide(Bomb& otherObject) { ; }
	virtual void collide(Fruit& otherObject) { ; }
	virtual void collide(Rock& otherObject) { ; }
	virtual void collide(Shot& otherObject) { ; }
	virtual void collide(SpaceShip& otherObject) { ; }
	void draw(sf::RenderWindow & window);
	void updateMove();
	void setAstroInside(bool c);
	bool isAstroInside() const;

private:
	bool m_astroInside;
	std::unique_ptr<Animation> m_r1;
	std::unique_ptr<Animation> m_r2;
};

