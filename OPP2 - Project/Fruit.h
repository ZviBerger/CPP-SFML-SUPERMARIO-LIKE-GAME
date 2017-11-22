#pragma once
#include "RemovableObj.h"
#include "TextBox.h"
class Fruit  :public RemovableObj, public ProcessInterface
{
public:
	Fruit(sf::Vector2f &scaling, sf::Vector2f& position);
	~Fruit();
	virtual void collide(GameObject& otherObject);
	virtual void collide(Alien& otherObject) { ; }
	virtual void collide(Astroid& otherObject) { ; }
	virtual void collide(Astronaut& otherObject);
	virtual void collide(Bomb& otherObject) { ; }
	virtual void collide(Fruit& otherObject) { ; }
	virtual void collide(Rock& otherObject) { ; }
	virtual void collide(Shot& otherObject) { ; }
	virtual void collide(SpaceShip& otherObject) { ; }
	virtual void draw(sf::RenderWindow &window);
	void eated(const bool &e);
	bool isEated() const;
	void updateMove();
	
private:
	bool m_eated;
	TextBox m_myTextBox;
};

