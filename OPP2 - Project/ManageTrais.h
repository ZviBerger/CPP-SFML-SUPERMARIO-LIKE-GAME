#pragma once
#include "Spark.h"
#include <list>
class ManageTrais {

public:
	static void addSpark(V2f & p, float indexZ,const float & time2live);
	static void removeAllTrails();
	static void updateMove();
	static void draw(sf::RenderWindow & window);
private:
	static std::list<std::unique_ptr<Spark>> m_trails;
	static std::list<std::unique_ptr<Spark>>initVec();
	static sf::Clock m_clock;
};
