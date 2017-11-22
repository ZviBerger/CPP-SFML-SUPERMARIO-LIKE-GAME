#pragma once
#include "MyExeption.h"
#include "ProcessInterface.h"
#include "Animation.h"
#include  <memory>
#include <map>
///////////////////////////////////////////////////////////////////////////////////
using V2f = sf::Vector2f;
///////////////////////////////////////////////////////////////////////////////////
enum Movments{RIGHT,LEFT,UP,DOWN,JUMP,SHOOT,GO,STOP,FALL,MOVE,ALL};
///////////////////////////////////////////////////////////////////////////////////
const sf::Vector2f windowSize(1280, 720);
///////////////////////////////////////////////////////////////////////////////////
static V2f operator+(V2f a, V2f b) { return{ a.x + b.x, a.y + b.y }; };
static V2f operator+=(V2f a, V2f b) { return a + b; };
static V2f operator*(V2f a, V2f b) { return{ a.x * b.x, a.y * b.y }; };
static V2f operator-(V2f a, V2f b) { return{ a.x - b.x, a.y - b.y }; };
static V2f operator/(V2f a, V2f b) { return{ a.x / b.x, a.y / b.y }; };
static V2f operator-=(V2f a, V2f b) { return{ a += -b }; };
///////////////////////////////////////////////////////////////////////////////////
struct ICenMove2 {
	bool _right;
	bool _left;
	bool _up;
	bool _down;
};
///////////////////////////////////////////////////////////////////////////////////

struct PhysicalValues {
	float _v0;  //first velosity
	float _g;   //the gravity
	float _t;
	float _angel; // the angel
};
///////////////////////////////////////////////////////////////////////////////////
namespace path2image {

	const std::string astronaut("images/astronaut.png");
	const std::string astroid("images/rock.png");
	const std::string alien("images/alien.png");
	const std::string bomb("images/explosions/bomb.png");
	const std::string fruit("images/fruit.png");
	const std::string rock("images/ground1.jpg");
	const std::string shot("images/fire_red.png");
	const std::string tree("images/tree.png");
	const std::string spaceShip{ "images/spaceShip.png" };
	const std::string rocketFire{ "images/fire_blue.png" };
	const std::string heart{ "images/heart.png" };

	const std::string backGround("images/background1.png");
	const std::string bg1("images/bg1.png");
	const std::string bg2("images/bg2.png");
	const std::string bg3("images/bg3.png");
	const std::string bg4("images/bg4.png");

	const std::string menu("images/menu.png");
	const std::string help{ "images/help.png" };
	const std::string nextLevel{ "images/next.png" };
	
};
///////////////////////////////////////////////////////////////////////////////////
namespace path2sound {
	const std::string laserGun{ "sounds/laserGun.ogg" };
	const std::string  endLevel{"sounds/endLevel.ogg" };
	const std::string  eatFruit{"sounds/eatFruit.ogg" };
    const std::string background{ "sounds/background.ogg" };
	const std::string  alienHit{"sounds/alienHit.ogg" };
	const std::vector<std::string>  explosions{ "sounds/explode1.ogg","sounds/explode2.ogg","sounds/explode3.ogg","sounds/explode4.ogg" , "sounds/explode5.ogg" };
	
};

