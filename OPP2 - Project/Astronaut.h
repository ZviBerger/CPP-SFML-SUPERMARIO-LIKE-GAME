#pragma once
#include "MovableObject.h"
class Astronaut : public MovableObject, public ProcessInterface
{
public:
	Astronaut(sf::Vector2f &scaling, sf::Vector2f& position);
	~Astronaut();
	virtual void updateMove();
	virtual void draw(sf::RenderWindow & window);
	virtual void collide(GameObject& otherObject);
	virtual void collide(Alien& otherObject);
	virtual void collide(Astroid& otherObject) { ; }
	virtual void collide(Astronaut& otherObject) { ; }
	virtual void collide(Bomb& otherObject) { ; }
	virtual void collide(Fruit& otherObject);
	virtual void collide(Rock& otherObject);
	virtual void collide(Shot& otherObject) { ; }
	virtual void collide(SpaceShip& otherObject);

	void setMove(Movments action, Movments side);
	void stop(Movments forbidenDir);
	void addLife() { m_lifesNum++; };
	void reduceLife() { m_lifesNum--; m_animNow = m_hit;};
	void addFruit() { m_fruitNum++; };
	void reduceFruit() { m_fruitNum--; };
	void setStandAnim(){ m_animNow = m_go; }
	int getLifesNum() { return m_lifesNum;  };
	int getFruitsNum() { return m_fruitNum; };
	void cameToShip() { m_cameToTarget = true; }
	bool didComeToShip()const { return m_cameToTarget; }
	bool isFalling() const { return m_falling; }
	bool isFalling2space() const { return m_falling2space; }
	bool isOutOfLifes() const { return m_lifesNum < 0; }
private:
	std::shared_ptr<Animation> m_go;
	std::shared_ptr<Animation> m_jump;
	std::shared_ptr<Animation> m_shoot;
	std::shared_ptr<Animation> m_hit;
	std::shared_ptr<Animation> m_animNow;
	struct PhysicalValues m_phv;
	struct ICanMove2 m_cm2;
	int m_fruitNum, m_lifesNum ,m_jumpCount;
	float m_dx,m_dy, m_accel;
	bool m_jumping, m_falling, m_moving, m_falling2space;
	bool m_cameToTarget = false;
};

