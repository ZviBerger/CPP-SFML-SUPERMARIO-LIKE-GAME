#include "InfoBar.h"






InfoBar::InfoBar(const V2f & position, const V2f & size, const int &stage, const int &score, const int & lives, sf::Time & time)

	:m_position(position), m_size(size), m_stage(stage), m_score(score), m_lives(lives), m_time(time),m_fruit(V2f{.2f,.2f},V2f(position))
{
	m_liveTxt.loadFromFile(path2image::heart);
	m_liveSpr.setTexture(m_liveTxt);
	m_liveSpr.setScale(sf::Vector2f{ .15f,.15f });

}

void InfoBar::setScore(int score)
{
	m_score = score;
}

void InfoBar::setTime(sf::Time time)
{
}

void InfoBar::setLive(int live)
{
	m_lives = live;
}

void InfoBar::setStage(int stage)
{
	m_stage = stage;
}

bool InfoBar::isAlive()
{
	return (m_lives >= 0 && !isTimeOver());
}

bool InfoBar::isTimeOver()
{
	return (m_time.asSeconds() - m_countdTimer.getElapsedTime().asSeconds()) <= 0;
}

void InfoBar::draw(sf::RenderWindow & w)
{
	backInTime();
	std::string hour = (m_hour < 10) ? "0" + std::to_string(m_hour) : std::to_string(m_hour);
	std::string minute = (m_minute < 10) ? "0" + std::to_string(m_minute) : std::to_string(m_minute);
	std::string sec = (m_seconds < 10) ? "0" + std::to_string(m_seconds) : std::to_string(m_seconds);

	std::string levelAndTime = "\n            Level: " + std::to_string(m_stage)
		+ "        " + "Time: " + hour + ": " + minute + ": " + sec + "              x  " + std::to_string(m_score);

	m_textBox.settings(levelAndTime, sf::Vector2f{ 1,1 }, m_position);
	m_textBox.draw(w);
	m_fruit.setPosition(sf::Vector2f{ m_position.x + 530 ,m_position.y + 45 });
	m_fruit.draw(w);
	for (int i = 0; i < m_lives; i++)
	{
		m_liveSpr.setPosition(sf::Vector2f{ m_position.x + i * 40 + 750 ,m_position.y + 35 });
		w.draw(m_liveSpr);
	}
}

int InfoBar::getScore() const
{
	return m_score;
}

void InfoBar::setPosition(sf::Vector2f & pos)
{
	m_position = pos;
}

void InfoBar::nexTime()
{
	auto tsec = int(m_countdTimer.getElapsedTime().asSeconds());
	m_hour = tsec / 3600;
	m_minute = tsec / 60;
	m_seconds = tsec % 60;
}

void InfoBar::backInTime()
{
	auto tsec = int(m_time.asSeconds() - m_countdTimer.getElapsedTime().asSeconds());
	m_hour = tsec / 3600;
	m_minute = tsec / 60;
	m_seconds = tsec % 60;

}
