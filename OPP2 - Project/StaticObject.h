#pragma once
#include "GameObject.h"
class StaticObject : public GameObject
{
public:
	StaticObject(sf::Vector2f &scaling,sf::FloatRect &fr);
	~StaticObject();
	virtual void draw(sf::RenderWindow & window);
	virtual bool collideWithMe(const sf::FloatRect & other);
	virtual void updateMove() { ; }
	void setSpriteTexture(sf::Texture &txt);
	void setTextureRect(sf::IntRect & iR);
	sf::Sprite& getSprite();
private:
	sf::Sprite m_sprite;
};

