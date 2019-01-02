#include "Rock.h"

Rock::Rock(sf::Vector2f &scaling, sf::Vector2f& position)
	:StaticObject(scaling, sf::FloatRect{ position.x,position.y,50,50 })
{
	static  sf::Texture txt{};
	static bool loaded = false;
	if (!loaded)
		loaded = txt.loadFromFile(path2image::rock);
	setSpriteTexture(txt);
	getSprite().setColor(sf::Color::White);

	//getSprite().setOrigin(V2f{ 25,25 });
	//getSprite().setScale(V2f{ rand() % 2 == 0 ? scaling.x : -scaling.x,rand() % 2 == 0 ? scaling.y: -scaling.y });
}

void Rock::collide(GameObject & otherObject)
{
	otherObject.collide(*this);
}

void Rock::collide(Astronaut & otherObject)
{
	astronautHitRock(otherObject, *this);
}

void Rock::collide(Shot & otherObject)
{
	shotHitRock(otherObject, *this);
}

