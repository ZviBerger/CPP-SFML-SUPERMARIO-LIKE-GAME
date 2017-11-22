#pragma once
#include "Utilities.h"
class GameManage
{
public:
	GameManage(sf::Texture &texture, sf::Vector2f position, sf::Vector2f size);
	~GameManage();
	sf::Vector2f  getSize() { return m_size; };
	sf::Vector2f  getPosition() { return m_position; };
	//void setPosition(sf::Vector2f pos) { m_position = pos; }

private:
	sf::Texture &m_texture;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
};

