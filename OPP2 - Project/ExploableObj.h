#pragma once
//#include "RemovableObj.h"
#include "Bomb.h"
class ExploableObj : public RemovableObj
{
public:
	ExploableObj(sf::Vector2f &scaling, sf::FloatRect &fr);
	virtual ~ExploableObj() = 0;
	void setIfHit(bool b);
	void updateMove();
protected:
	bool m_hit;
	bool m_setedAnim;
	std::unique_ptr<Bomb> m_myBomb;
};

