#include "Animation.h"
//////////////////////////////////////////////////////
/// Ctor 1
//////////////////////////////////////////////////////
Animation::Animation(sf::Texture &txt, const int &startX, const int &startY,
	const int &w, const int &h, const int &framesNumber, const float &speed)
	:m_frame(0), m_speed(speed)
{
	for (int i = 0; i< framesNumber ; i++)
		m_frames.push_back(sf::IntRect(startX + i*w, startY, w, h));

	m_sprite.setTexture(txt);
	m_sprite.setOrigin(w / 2, h / 2);
	m_sprite.setTextureRect(m_frames[0]);
}
//////////////////////////////////////////////////////
/// Ctor 2
//////////////////////////////////////////////////////
Animation::Animation(sf::Texture & txt, const std::vector<sf::IntRect> frames, const float & speed)
	:m_frame(0), m_speed(speed)
{
	m_frames = frames;
	m_sprite.setTexture(txt);
	m_sprite.setTextureRect(m_frames[0]);
}

//////////////////////////////////////////////////////
/// update
//////////////////////////////////////////////////////
void Animation::updateAnim()
{
	m_frame += m_speed;
	int n = m_frames.size(); // n is number of frames
	if (m_frame >= n)
	{
		m_frame -= n;
		m_end = true;
	}
	if (n>0)
		m_sprite.setTextureRect(m_frames[int(m_frame)]);
}
//////////////////////////////////////////////////////
///  GetSprite
//////////////////////////////////////////////////////

sf::Sprite & Animation::getSprite()
{
	return m_sprite;
}
void Animation::setPosition(sf::Vector2f & pos)
{
	m_sprite.setPosition(pos);
}
sf::Vector2f Animation::getPosition()
{
	return m_sprite.getPosition();
}
//////////////////////////////////////////////////////
/// isEnd
//////////////////////////////////////////////////////

bool Animation::isEnd()
{  // m_frame + m_speed >= m_frames.size();
	return m_end;
}
