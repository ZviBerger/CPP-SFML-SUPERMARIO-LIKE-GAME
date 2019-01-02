#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
/////////////////////////////////////////////////////////////////////
//Ainmation Class:
//Ctor Args: texture by ref, 
//size of any frame from the texture: startX , startY, width, high,
//Number of all Fraames: framesNumber
//Speed of aimation.
//-------------------------------------------------------------------
//API:
//void updateAnim() -
//sf::Sprite & GetSprite() -
//bool isEnd()-
///////////////////////////////////////////////////////////////////////
class Animation
{
public:

	Animation(sf::Texture &txt, const int &startX, const int &startY,
		const int &w, const int &h, const int &framesNumber, const float &Speed);
	Animation(sf::Texture &txt, const std::vector<sf::IntRect> frames,const float& speed);
	void updateAnim();
	sf::Sprite & getSprite();
	void setPosition(sf::Vector2f &pos);
	sf::Vector2f getPosition();
	bool isEnd();
	void setSpeed(const float &newSpeed) { m_speed = abs(newSpeed); };
private:
	bool m_end = false;
	float m_frame;
	float m_speed;
	sf::Sprite m_sprite;
	std::vector<sf::IntRect> m_frames;
	
};

