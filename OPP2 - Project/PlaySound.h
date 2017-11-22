#pragma once
//#include "Controller.h"
#include <SFML/Audio.hpp>
#include<vector>
const unsigned EXNUM = 5;


class PlaySound
{
public:
	PlaySound();
	~PlaySound();
	void playAlienHit();
	void playExplode();
	void playLaserGun();
	void playEndLevel();
	void playEatFruit();
	void playBackground();

private:

	sf::Music m_alienHit;
	sf::Music m_laserGun;
	sf::Music m_endLevel;
	sf::Music m_eatFruit;
	sf::Music m_background;
	std::vector<sf::Music> m_explosionsVec{ EXNUM };
	std::vector<unsigned> m_exVolVec{ 50,80,30,50,80 };
};

