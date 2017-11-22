#pragma once
#include "Utilities.h"
class GameObject;
typedef std::shared_ptr<GameObject>(*myFuncPtr)(sf::Vector2f &scaling, sf::Vector2f& position) ;
typedef std::map<std::string, std::shared_ptr<GameObject>(*)(V2f &scaling, V2f& position)> myMapType;

class Factory {
public:
	static  std::shared_ptr<GameObject> create(const std::string& name,V2f &scaling, V2f& position);
	static bool registerit(const std::string& name, std::shared_ptr<GameObject>(*f)(V2f &scaling, V2f &position));
private:
	static myMapType m_map;
    static myMapType createMap();

};
