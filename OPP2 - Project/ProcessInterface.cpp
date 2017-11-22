#include "ProcessInterface.h"
#include "Astronaut.h"
#include "Astroid.h"
#include "Shot.h"
#include "Alien.h"
#include "Rock.h"
#include "Tree.h"
#include "Fruit.h"
#include "SpaceShip.h"
////////////////////////constant///////////////////////////////////
 const int EPSX = 10;
 const int EPSY = 30;
 const int SECONST = 3;
PlaySound ProcessInterface::m_sound{};
////////////////////////////////////////////////////////////////////
ProcessInterface::ProcessInterface()
{
}

ProcessInterface::~ProcessInterface()
{
}
////////////////////////////////////////////////////////////////////
void ProcessInterface::astroidHitAlien(Astroid & astr, Alien & ali)
{
	if (astr.collideWithMe(ali.getGlobalBounds()))
	{
		m_sound.playAlienHit();
		m_sound.playExplode();
		astr.setIfHit(true);
		ali.setLive(false);
	}
}
////////////////////////////////////////////////////////////////////
void ProcessInterface::astroidHitAstronout(Astroid & astr, Astronaut & atron)
{
	static bool hitOnceAstr = false;
	static sf::Clock clockHitAstr{};
	
	if (astr.collideWithMe(atron.getGlobalBounds())) {
		if (!hitOnceAstr)
		{
			atron.reduceLife();
			clockHitAstr.restart();
			hitOnceAstr = true;
		}
		astr.setIfHit(true);
	}
}
////////////////////////////////////////////////////////////////////
void ProcessInterface::astroidHitRock(Astroid & astr, Rock & rock)
{
	if (astr.collideWithMe(rock.getGlobalBounds())) {
		m_sound.playExplode();
		astr.setIfHit(true);
		rock.setLive(false);
	}
}
////////////////////////////////////////////////////////////////////
void ProcessInterface::astroidHitShot(Astroid & astr, Shot & shot)
{
	if (astr.collideWithMe(shot.getGlobalBounds()))
	{
		m_sound.playExplode();
		astr.setIfHit(true);
		shot.setLive(false);
	}
}
////////////////////////////////////////////////////////////////////
void ProcessInterface::astronautHitAlien(Astronaut & astron, Alien & ali)
{
	static bool hitOnce = false;
	static sf::Clock clockHit{};

	if (hitOnce && clockHit.getElapsedTime().asSeconds() >= SECONST)
		hitOnce = false;

	if (astron.collideWithMe(ali.getGlobalBounds()))
	{
		if (!hitOnce)
		{
			hitOnce = true;
			astron.reduceLife();
			clockHit.restart();
			m_sound.playAlienHit();

		}

		ali.changeSide();
	}
}
////////////////////////////////////////////////////////////////////
void ProcessInterface::astronautHitRock(Astronaut & astron, Rock & rock)
{
	
	if (!astron.collideWithMe(rock.getGlobalBounds()))return;
	
	sf::FloatRect ast = astron.getGlobalBounds();
	sf::FloatRect roc = rock.getGlobalBounds();
	auto BL = V2f{ ast.left + EPSX  ,ast.top + ast.height };
	auto BR = V2f{ ast.left + ast.width-EPSX ,ast.top + ast.height };

	auto TR = V2f{ ast.left + ast.width-EPSX,ast.top };
	auto TL = V2f{ ast.left + EPSX ,ast.top };
	
	auto MR1 = V2f{ ast.left + ast.width ,ast.top + ast.height / 2 + EPSY };
	auto MR2 = V2f{ ast.left + ast.width ,ast.top + ast.height / 2  };
	auto MR3 = V2f{ ast.left + ast.width ,ast.top + ast.height / 2 -EPSY };
	
	auto ML1 = V2f{ ast.left ,ast.top + ast.height / 2 + EPSY };
	auto ML2 = V2f{ ast.left ,ast.top + ast.height / 2  };
	auto ML3 = V2f{ ast.left ,ast.top + ast.height / 2 - EPSY };

	if (rock.contains(BL) || rock.contains(BR))
			astron.setMove(STOP, DOWN);
	if (rock.contains(TL) || rock.contains(TR))
		    astron.setMove(STOP, UP);
	if (rock.contains(MR1)|| rock.contains(MR2) || rock.contains(MR3))
			astron.setMove(STOP, RIGHT);
	if (rock.contains(ML1)|| rock.contains(ML2) || rock.contains(ML3))
			astron.setMove(STOP, LEFT);
}
////////////////////////////////////////////////////////////////////
void ProcessInterface::astronautHitFruit(Astronaut & astron, Fruit & fruit)
{
	
	if (astron.collideWithMe(fruit.getGlobalBounds())&& !fruit.isEated())
	{

		m_sound.playEatFruit();
		fruit.eated(true);
		astron.addFruit();
	}
}
////////////////////////////////////////////////////////////////////
void ProcessInterface::astronautHitSpaceShip(Astronaut & astron, SpaceShip & sp)
{
	
	if (astron.collideWithMe(sp.getGlobalBounds()) && !sp.isAstroInside())
	{ 
		float  astX = astron.getGlobalBounds().left +astron.getGlobalBounds().width/2;
		float  ssX = sp.getGlobalBounds().left + sp.getGlobalBounds().width / 2;
		

		if (astX<ssX - EPSX || astX > ssX + EPSX)
			return;
		
		sp.setAstroInside(true);
		m_sound.playEndLevel();
		astron.cameToShip();
	}
}
////////////////////////////////////////////////////////////////////
void ProcessInterface::alienHitShot(Alien & ali, Shot & shot)
{
	if (ali.collideWithMe(shot.getGlobalBounds()))
	{
		m_sound.playExplode();
		m_sound.playAlienHit();
		shot.setIfHit(true);
		ali.setLive(false);
	}
}
////////////////////////////////////////////////////////////////////
void ProcessInterface::alienHitRock(Alien & ali, Rock & rock)
{
	
	auto aliBnd =ali.getGlobalBounds();
    if (!rock.collideWithMe(aliBnd))return;

	auto BL = V2f{aliBnd.left  ,aliBnd.top + aliBnd.height };
	auto BR = V2f{aliBnd.left + aliBnd.width , aliBnd.top + aliBnd.height };
	auto BM = V2f{ aliBnd.left + aliBnd.width/2,aliBnd.top + aliBnd.height };
	auto ML = V2f{aliBnd.left, aliBnd.top+aliBnd.height/2 + EPSY };
	auto MR = V2f{aliBnd.left+aliBnd.width, aliBnd.top + aliBnd.height / 2 + EPSY };
	
	if (rock.contains(BL) || rock.contains(BR)|| rock.contains(BM))
		ali.setFallMode(false);
	else
	    ali.setFallMode(true);
	

	if (rock.contains(ML) || rock.contains(MR))
		ali.changeSide();

}
////////////////////////////////////////////////////////////////////