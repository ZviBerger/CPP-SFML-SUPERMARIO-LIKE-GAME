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
	setTextureRect(sf::IntRect{  0 , 0 , 257 ,321 });
	
}

void Rock::collide(GameObject & otherObject)
{
	otherObject.collide(*this);
}

void Rock::collide(Astronaut & otherObject)
{
	astronautHitRock(otherObject, *this);
}

