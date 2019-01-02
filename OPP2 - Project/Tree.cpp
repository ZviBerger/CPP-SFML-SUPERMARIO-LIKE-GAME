#include "Tree.h"



Tree::Tree(sf::Vector2f &scaling, sf::Vector2f& position)
	: StaticObject(scaling, sf::FloatRect{ position.x,position.y,350,500 })
{
	static sf::Texture txt{};
	static bool loaded = false;
	if (!loaded)
	loaded = txt.loadFromFile(path2image::tree);
	setSpriteTexture(txt);
	getSprite().setColor(getRandomColor());
}




