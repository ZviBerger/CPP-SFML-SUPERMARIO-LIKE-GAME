#pragma once
#include "RelativelyMovingObj.h"

class Spark : public RelativelyMovingObj
{
public:
	Spark( V2f & position, float zIndex, float time2live);
	~Spark();
	
	virtual void draw(sf::RenderWindow & window);
	virtual void updateMove();
	virtual void updateMove(const sf::Vector2f &relativePos);
	void setColor(sf::Color c);
	sf::FloatRect getFloatRect() const { return m_cs.getGlobalBounds();  }
private:
    sf::Sprite m_cs;
	V2f m_movingFactor;
	float m_dx;
	float m_dy;
	float m_dz;
	float m_time2live;
	
};

