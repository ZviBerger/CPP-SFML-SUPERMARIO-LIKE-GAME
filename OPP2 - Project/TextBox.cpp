#include "TextBox.h"





TextBox::TextBox()
{
	std::string fontFileName = getWinDirName() + "/fonts/arial.ttf";
	m_font.loadFromFile(fontFileName);
	m_text.setPosition(m_position);
	m_text.setFont(m_font);
	m_text.setCharacterSize(30);
	m_text.setFillColor(sf::Color::Color(0,0,0,250));
	m_text.setOutlineColor(sf::Color::White);
	m_text.setOutlineThickness(2);
}

TextBox::TextBox(const std::string & contain, sf::Vector2f position)
	:m_position(position)
{

	m_text.setPosition(position);
	m_text.setString(contain);
	std::string fontFileName = getWinDirName() + "/fonts/arial.ttf";
	m_font.loadFromFile(fontFileName);
	m_text.setFont(m_font);
	m_text.setCharacterSize(30);
	m_text.setFillColor(sf::Color::Color(0, 0, 0, 250));
	m_text.setOutlineColor(sf::Color::White);
	m_text.setOutlineThickness(2);
}



void TextBox::settings(const std::string & contain, sf::Vector2f & scaling, sf::Vector2f & position)
{
	m_position = position;
	m_text.setPosition(position);
	m_text.setString(contain);
	m_text.setScale(scaling);
	
	
}

void TextBox::draw(sf::RenderWindow & w)
{
	m_text.setPosition(m_position);
	w.draw(m_text);
}

void TextBox::editString(std::string & newStr)
{
	m_text.setString(newStr);
}

void TextBox::editCharSize(const int newSize)
{
	m_text.setCharacterSize(newSize);
}

void TextBox::setPosition(sf::Vector2f & pos)
{
	m_position = pos;
}

std::string TextBox::getWinDirName()
{
	size_t envSize;
	std::string winDirName(1, ' ');
	auto ret = getenv_s(&envSize, &winDirName[0], winDirName.size(), "WINDIR");
	winDirName.resize(envSize);
	ret = getenv_s(&envSize, &winDirName[0], winDirName.size(), "WINDIR");
	winDirName.resize(envSize - 1); // remove the null-terminator
	return winDirName;
}
