#pragma once
#include "GameObject.h"

class MovableObject : public GameObject
{
public:
	MovableObject(sf::Vector2f &scaling, sf::FloatRect &fr);
	virtual void draw(sf::RenderWindow & window);
	void setAnim(std::shared_ptr<Animation>& anim);
	virtual void go2(sf::Vector2f& location);
	virtual bool collideWithMe(const sf::FloatRect & other);
	//virtual void updateMove()=0;
	std::shared_ptr<Animation> getAnim();
	//bool isValidMove() const;
protected:
	sf::Clock m_clock;
private:
	std::shared_ptr<Animation> m_objAnimPtr;
};

