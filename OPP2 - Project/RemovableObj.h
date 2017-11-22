#pragma once
#include "MovableObject.h"

class RemovableObj : public MovableObject
{
public:
	RemovableObj(sf::Vector2f &scaling,sf::FloatRect & fr);
	virtual void updateMove() = 0;
private:
	
};

