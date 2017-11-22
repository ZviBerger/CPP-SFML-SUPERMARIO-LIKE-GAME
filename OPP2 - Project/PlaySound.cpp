#include "PlaySound.h"
#include "Utilities.h"


PlaySound::PlaySound()
{

	m_alienHit.openFromFile(path2sound::alienHit);
	m_background.openFromFile(path2sound::background);
	m_eatFruit.openFromFile(path2sound::eatFruit);
	m_endLevel.openFromFile(path2sound::endLevel);
	m_laserGun.openFromFile(path2sound::laserGun);

	for (size_t i = 0; i < 5; i++)
	{
		m_explosionsVec[i].openFromFile(path2sound::explosions[i]);
		m_explosionsVec[i].setVolume(m_exVolVec[i]);
	}

	m_alienHit.setVolume(50);
	m_background.setVolume(100);
	m_eatFruit.setVolume(50);
	m_endLevel.setVolume(90);
	m_laserGun.setVolume(40);

}


PlaySound::~PlaySound()
{
}

void PlaySound::playAlienHit()
{
	m_alienHit.play();
}

void PlaySound::playExplode()
{
	m_explosionsVec[rand() % EXNUM].play();
}

void PlaySound::playLaserGun()
{
	m_laserGun.play();
}

void PlaySound::playEndLevel()
{
	m_endLevel.play();
}

void PlaySound::playEatFruit()
{
	m_eatFruit.play();
}

void PlaySound::playBackground()
{
	
	m_background.play();
	m_background.setLoop(true);
}
