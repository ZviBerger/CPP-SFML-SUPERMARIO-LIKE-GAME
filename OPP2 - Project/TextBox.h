#pragma once
#include "GameObject.h"
#include <string>
class TextBox 
{
public:
	TextBox();
	TextBox(const std::string & contain, sf::Vector2f position);
	
	void settings(const std::string & contain, sf::Vector2f & scaling, sf::Vector2f & position);
	void draw(sf::RenderWindow &w);
	void editString(std::string &newStr);
	void editCharSize(const int newSize = 30);
	void setPosition(sf::Vector2f &pos);

private:

	sf::Vector2f m_position = V2f{ 0,0 };
	sf::Font m_font;
	sf::Text m_text;
	std::string getWinDirName();
	
};

