#pragma once
#include "GameObject.h"
#include <vector>
#include "RelativelyMovingObj.h"
using SingleScreen = std::pair<sf::RectangleShape, V2f>;
static sf::Color getRandomColor() {
using namespace sf;

static const std::vector<Color> colors{ Color::Yellow,Color::Blue,Color::Cyan,Color::Green,Color::Magenta,Color::Red };
return colors[rand() % colors.size()];

};

class layer
{
public:
	layer(sf::Texture& t,const V2f& size,const V2f &pos, const float& distn)
		:m_size(size), m_bg1(size), m_bg2(size), m_pos1(V2f{ pos.x-size.x / 2,pos.y }), m_pos2(V2f{ pos.x+size.x/2,pos.y }), m_distn(distn)
	{
		m_bg1.setTexture(&t);
		m_bg2.setTexture(&t);
		m_bg1.setScale(V2f{ 1,0.5 });
		m_bg2.setScale(V2f{ 1,0.5 });
		m_bg1.setPosition(m_pos1);
		m_bg2.setPosition(m_pos2);
	
		m_bg1.setOutlineColor(getRandomColor());
		m_bg2.setOutlineColor(getRandomColor());
		m_bg1.setOutlineThickness(5);
		m_bg2.setOutlineThickness(10);
	}

	void move(const Movments& direc,V2f & factor,sf::FloatRect & mainBg) {
		
			m_pos1.x -= (factor.x / m_distn) * 20;
			m_pos2.x -= (factor.x / m_distn) * 20;
			m_pos1.y = m_pos2.y = mainBg.top + mainBg.height - m_distn - 250;
		

			if (!mainBg.intersects(m_bg1.getGlobalBounds()))
				m_pos1.x = m_pos2.x + (direc == RIGHT) ? + m_size.x : -m_size.x;

			if (!mainBg.intersects(m_bg2.getGlobalBounds()))
				m_pos2.x = m_pos1.x + (direc == RIGHT) ? + m_size.x : -m_size.x;
		/*if (direc == RIGHT) {
			if (!mainBg.intersects(_bg1.getGlobalBounds()))

		}
*/

		m_bg1.setPosition(m_pos1);
		m_bg2.setPosition(m_pos2);

	}
	void draw(sf::RenderWindow &w)
	{
		w.draw(m_bg1);
		w.draw(m_bg2);
	}
	sf::RectangleShape m_bg1,m_bg2;
	V2f m_pos1,m_pos2,m_size;
	float m_distn;
};


class Background 
{
public:
	Background();
	~Background();
	virtual void draw(sf::RenderWindow & window);
	virtual void updateMove();
	void setPosition(const V2f&);
	V2f getPosition() const { return m_mainBGP; }
private:
	sf::RectangleShape  m_mainBG;
	V2f m_mainBGP;
	std::vector<layer> m_layers;
	std::vector<std::unique_ptr<RelativelyMovingObj>> m_spaceObjects;
	Movments m_direction;
	V2f m_factor;
	bool m_moved;
	void findNextDir(const V2f &newPos);
};

