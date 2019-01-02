#pragma once
#include <fstream>
#include <functional>
#include "GameManage.h"
#include "InfoBar.h"
#include "Astronaut.h"
#include "Astroid.h"
#include "Shot.h"
#include "Alien.h"
#include "Rock.h"
#include "Tree.h"
#include "SpaceShip.h"
#include "Fruit.h"
#include "Background.h"

typedef  std::pair<size_t, std::shared_ptr<GameObject>>   gamePairType;
typedef std::vector<gamePairType>::iterator myVecIterator;


class ViewStation 
{
public:
	ViewStation(std::string level, unsigned levelNum);
	~ViewStation();
	bool isGameOver() const;
	bool finishLevel();
	void drawView(sf::RenderWindow &w);
	void loadGameObjects();
	void checkCollide();
	void updateMove(Movments movmentMode, Movments side2move);
	void addShot(Movments side2move);
	void astroSetMove(Movments move, Movments side2move);
	int getScore();
	sf::Vector2f getViewPosition()const;
	

private:
	std::vector<gamePairType> m_graph;
	std::vector<std::shared_ptr<GameObject>> m_movableVec; 
	std::ifstream m_theFile;
	std::unique_ptr<InfoBar> m_info;
	std::shared_ptr<Astronaut> m_astronaut;
	std::map < char, std::function<void(V2f  & p)> > m_charsMap;
	std::unique_ptr<Background> m_bg;
	sf::View m_view;
	sf::Texture m_bgtxt;
	sf::FloatRect m_windowRec;
	size_t m_rowsNum;
	size_t m_colsNum;
	unsigned int m_level;
	
	static PlaySound m_sound;
	sf::Clock m_fallingTime;

	void updateCharsMap();
	void setTheGraph(std::string level);
	std::pair<size_t, std::shared_ptr<GameObject>> getNewObj(std::string str, size_t l, V2f s, V2f p);

};

