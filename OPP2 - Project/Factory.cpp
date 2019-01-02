#include "Factory.h"
#include "GameObject.h"
#include "Astronaut.h"
#include "Astroid.h"
#include "Shot.h"
#include "Alien.h"
#include "Rock.h"
#include "Tree.h"
#include "Fruit.h"
#include "SpaceShip.h"

myMapType Factory::m_map = createMap();
////////////////////////////////////////////////////////////////////

myMapType Factory::createMap()
{
	myMapType newMap;
	newMap["Astronaut"] = [](V2f &s, V2f& p)->std::shared_ptr<GameObject> {return std::make_shared<Astronaut>(s, p); };
	newMap["Astroid"] =   [](V2f &s, V2f& p)->std::shared_ptr<GameObject> {return std::make_shared<Astroid>(s, p); };
	newMap["Alien"] =     [](V2f &s, V2f& p)->std::shared_ptr<GameObject> {return std::make_shared<Alien>(s, p); };
	newMap["Shot"] =      [](V2f &s, V2f& p)->std::shared_ptr<GameObject> {return std::make_shared<Shot>(s, p); };
	newMap["Tree"] =      [](V2f &s, V2f& p)->std::shared_ptr<GameObject> {return std::make_shared<Tree>(s, p); };
	newMap["Fruit"] =     [](V2f &s, V2f& p)->std::shared_ptr<GameObject> {return std::make_shared<Fruit>(s, p); };
	newMap["SpaceShip"] = [](V2f &s, V2f& p)->std::shared_ptr<GameObject> {return std::make_shared<SpaceShip>(s, p); };
	newMap["Rock"] =      [](V2f &s, V2f& p)->std::shared_ptr<GameObject> {return std::make_shared<Rock>(s, p); };

	return newMap;
}
////////////////////////////////////////////////////////////////////

std::shared_ptr<GameObject> Factory::create(const std::string & name, V2f & scaling, V2f & position)
{
	auto it = m_map.find(name);
	if (it == m_map.end())
		return nullptr;

	return it->second(scaling, position);
}

////////////////////////////////////////////////////////////////////

bool Factory::registerit(const std::string & name, std::shared_ptr<GameObject>(*f)(V2f &scaling, V2f &position))
{
	m_map.emplace(name, f);
	return true;
}
