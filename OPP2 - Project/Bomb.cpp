#include "Bomb.h"



Bomb::Bomb(sf::Vector2f &scaling, sf::Vector2f& position)
	:RemovableObj(scaling, sf::FloatRect{ position.x,position.y,100,100 })
{
	static  sf::Texture txt{};
	static bool loaded = false;
	if (!loaded)
		loaded= txt.loadFromFile(path2image::bomb);
	
	setAnim(std::make_shared<Animation>(txt, 0, 0, 192, 192, 64, 0.5));
}

void Bomb::collide(GameObject & otherObject)
{
	otherObject.collide(*this);
}


