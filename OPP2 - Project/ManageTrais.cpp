#include "ManageTrais.h"

sf::Clock ManageTrais::m_clock{};

std::list<std::unique_ptr<Spark>> ManageTrais::initVec()
{
	return std::list<std::unique_ptr<Spark>>();
}

std::list<std::unique_ptr<Spark>> ManageTrais::m_trails = initVec();


void ManageTrais::addSpark(V2f & p, float indexZ,const float & time2live) {
	m_trails.push_back(std::make_unique <Spark>(V2f{ rand() % 30 - 15 +p.x, rand() % 30 - 15 + p.y }, indexZ, time2live));
}
void ManageTrais::removeAllTrails()
{
	m_trails.clear();
}
void ManageTrais::updateMove() {

	for (auto &s : m_trails)
			s->updateMove();
	
	
		m_trails.erase(std::remove_if(m_trails.begin(), m_trails.end(),
			[](const std::unique_ptr<Spark> &sp) {return !sp->isAlive(); }), m_trails.end());
	

}
void ManageTrais::draw(sf::RenderWindow & window) {
  for (auto &spark : m_trails)
	spark->draw(window);
}
