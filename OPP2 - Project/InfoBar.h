#pragma once
#include "TextBox.h"
#include "Fruit.h"
class InfoBar 
{
public:
	InfoBar(const V2f & position,const V2f & size,const int &stage, const int &score, const int & lives, sf::Time & time);
	int getScore()const;
	void setScore(int score);
	void setTime(sf::Time time);
	void setLive(int live);
	void setStage(int stage);
	void setPosition(sf::Vector2f &pos);
	void draw(sf::RenderWindow &w);
	bool isAlive();
	bool isTimeOver();
private:
	int	 m_stage, m_lives, m_score;
	int m_hour = 0, m_minute = 0, m_seconds = 0;
	sf::Sprite m_liveSpr;
	Fruit m_fruit;
	sf::Texture m_liveTxt,m_fruitTxt;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	sf::Time m_time;
	sf::Clock m_countdTimer;
	TextBox  m_textBox;
	void nexTime();
	void backInTime();
};

