#pragma once


class Alien;
class Astroid;
class Astronaut;
class Bomb;
class Fruit;
class Rock;
class Shot;
class SpaceShip;
#include "PlaySound.h"

class ProcessInterface
{
public:
	ProcessInterface();
	~ProcessInterface();
	void astroidHitAlien(Astroid &astr, Alien &ali);
	void astroidHitAstronout(Astroid &astr, Astronaut &atron);
	void astroidHitRock(Astroid &astr, Rock &rock);
	void astroidHitShot(Astroid &astr, Shot &shot);

	void astronautHitAlien(Astronaut &astron, Alien &ali);
	void astronautHitRock(Astronaut &astron, Rock &rock);
	void astronautHitFruit(Astronaut &astron, Fruit &fruit);
	void astronautHitSpaceShip(Astronaut &astron, SpaceShip &sp);

	void shotHitRock(Shot & shot, Rock &rock);

	void alienHitShot(Alien &ali, Shot &shot);
	void alienHitRock(Alien &ali, Rock &rock);
private:
	 static PlaySound m_sound;
};

