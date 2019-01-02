#pragma once
#include "Utilities.h"
#include "Factory.h"

class Alien;
class Astroid;
class Astronaut;
class Bomb;
class Fruit;
class Rock;
class Shot;
class SpaceShip;

class GameObject
{
public:
	GameObject(sf::Vector2f &scaling, sf::FloatRect &fr);
	virtual bool collideWithMe(const sf::FloatRect & other) = 0;
	virtual void draw(sf::RenderWindow & window) = 0;
	virtual void collide(GameObject& otherObject) = 0;
	virtual void collide(Alien&      otherObject) = 0;
	virtual void collide(Astroid&    otherObject) = 0;
	virtual void collide(Astronaut&  otherObject) = 0;
	virtual void collide(Bomb&       otherObject) = 0;
	virtual void collide(Fruit&      otherObject) = 0;
	virtual void collide(Rock&       otherObject) = 0;
	virtual void collide(Shot&       otherObject) = 0;
	virtual void collide(SpaceShip&  otherObject) = 0;
	
	virtual void updateMove()=0;

	void setPosition(sf::Vector2f &toMove);
	void setScaling(sf::Vector2f &scaling);
	void setLive(bool b);
	void setWasBorn(bool birth);
	bool isAlive() const;
	bool wasBorn();
	bool contains(sf::Vector2f& point);
	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getScale() const;
	sf::Color GameObject::getRandomColor() const;
	

private:
	sf::FloatRect m_myFloatRect;
	sf::Vector2f m_position;
	sf::Vector2f m_scaling;
	bool m_alive;
	bool m_born;
};

