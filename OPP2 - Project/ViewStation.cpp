#include "ViewStation.h"
#include <math.h>
#include <exception>
#include "ManageTrais.h"
#include "Fog.h"
TextBox objectNumDebuging{ "NONE",V2f{0,0} };

//////////////////////////////////////////////////////////////////////
// static vars
/////////////////////////////////////////////////////////////////////
PlaySound ViewStation::m_sound{};
////////////////////////////////////////////////////////////////////
//operators 
////////////////////////////////////////////////////////////////////
sf::VideoMode operator/(const sf::VideoMode & mode, unsigned denom)
{
	return{ mode.width / denom,mode.height / denom , mode.bitsPerPixel };
}
/////////////////////////////////////////////////////////////////////
sf::Vector2f operator/(const sf::Vector2f & vec, unsigned num)
{
	return{ vec.x / num,vec.y / num };
}


///////////////////////////////////////////////////////////////////////
//sf::Vector2f operator-(const sf::Vector2f & v1, const sf::Vector2f & v2)
//{
//	return { v1.x - v2.x,v1.y - v2.y };
//} 
//sf::Vector2f operator+(const sf::Vector2f & v1, const sf::Vector2f & v2)
//{
//	return { v1.x + v2.x,v1.y + v2.y };
//}
////////////////////////////////////////////////////////////////////
// C-tor
////////////////////////////////////////////////////////////////////
ViewStation::ViewStation(std::string level, unsigned levelNum)
	:m_view(V2f{ 0,0 },windowSize ), 
	m_level(levelNum),
	m_astronaut(std::make_shared<Astronaut>(V2f{ 1,1 }, V2f{ 0,100 })),
	m_bg(std::make_unique<Background>()),
    m_info(std::make_unique<InfoBar>(V2f{ 0,0 }, V2f{ 1200, 60 }, levelNum, 0, 5, sf::Time{ sf::seconds(4*60.0f) }))

{
	objectNumDebuging.editCharSize(20);

	m_astronaut->setWasBorn(true);
	/*gamePairType player = std::make_pair(2, m_astronaut);
	m_graph.push_back(player);
	m_movableVec.push_back(m_astronaut);*/


	m_theFile.open(level);
	//set the intire object from the file to the vectors
	loadGameObjects();
	
	m_bgtxt.loadFromFile(path2image::backGround);

	
	//sorting the graph in order to print in liaers
	std::sort(m_graph.begin(), m_graph.end(), [&](gamePairType&left, gamePairType&right)
	{  return left.first < right.first; });
	
	m_sound.playBackground();
	m_windowRec = sf::FloatRect{ 0,0,windowSize.x+ 270,windowSize.y+270 };
	
	m_view.zoom(1.2);



}

ViewStation::~ViewStation()
{
	ManageTrais::removeAllTrails();
}
////////////////////////////////////////////////////////////////////
// isGameOver
////////////////////////////////////////////////////////////////////
bool ViewStation::isGameOver() const
{
	return m_astronaut->isOutOfLifes() || m_astronaut->isFalling2space() || m_info->isTimeOver() ;
}
////////////////////////////////////////////////////////////////////
// drawView
////////////////////////////////////////////////////////////////////
void ViewStation::drawView(sf::RenderWindow & myWindow)
{
	auto pos = m_astronaut->getPosition();
	m_view.setCenter(V2f{ pos.x,pos.y -100 });
	myWindow.setView(m_view);
	m_info->setScore(m_astronaut->getFruitsNum() * 100);
	m_info->setLive(m_astronaut->getLifesNum());
	
	auto realPos = m_view.getCenter() - windowSize / 2;
	m_bg->setPosition(realPos - V2f{130,100});//MMMMMMMMMMMM

	m_windowRec.left = realPos.x -140;
	m_windowRec.top = realPos.y - 100;
	
	myWindow.clear();
	//myWindow.draw(m_background);
	m_bg->draw(myWindow);
	for (auto &entity : m_graph){
		//draw the object only if it (or some of it) is inside the window wiew
		if(m_windowRec.intersects(entity.second->getGlobalBounds()))
			entity.second->draw(myWindow);
	}  

	ManageTrais::draw(myWindow);
	if(!m_astronaut->didComeToShip())
	     m_astronaut->draw(myWindow);

	m_info->draw(myWindow);
	
	/*##############DEBUGGING CODE>>>>
	
	TextBox p{ "0,0", V2f{0,0} };
	p.draw(myWindow);
	TextBox p2{ "100,100", V2f{ 100,100 } };
	p2.draw(myWindow);

	TextBox p3{ "100,0", V2f{ 100,0 } };
	p3.draw(myWindow);


	sf::RectangleShape bounders{};
	bounders.setOutlineColor(sf::Color::Red);
	bounders.setFillColor(sf::Color::Color(1, 1, 1, 0));
	bounders.setOutlineThickness(3);
	bounders.setSize(V2f{ m_windowRec.width, m_windowRec.height });
	bounders.setPosition(V2f{ m_windowRec.left,m_windowRec.top });
	myWindow.draw(bounders);
	int size=0;
	for (auto &obj : m_graph)
		if (obj.second->wasBorn())
			size++;
	objectNumDebuging.editString("Total Obj:"+std::to_string(m_graph.size())+"\nWas Born obj:"+ std::to_string(size));
	objectNumDebuging.setPosition(m_astronaut->getPosition() - V2f{30, 60});
	objectNumDebuging.draw(myWindow);
	//###############<<<<DEBUGGING CODE*/
}

////////////////////////////////////////////////////////////////////
// setTheGraph
////////////////////////////////////////////////////////////////////
void ViewStation::setTheGraph(std::string level)
{
	m_theFile.open(level);
	loadGameObjects();
}


////////////////////////////////////////////////////////////////////
//checkColide - manage the colutions between the objects 
////////////////////////////////////////////////////////////////////
void ViewStation::checkCollide()
{
	m_astronaut->setMove(MOVE, ALL);
	//Collutions checking
	for (auto &a : m_graph)
	{
		//check collution only for object inside the window or born obj
		if (m_windowRec.intersects(a.second->getGlobalBounds())||a.second->wasBorn())
		{
			m_astronaut->collide(*a.second);
			for (auto &b : m_graph)
				a.second->collide(*b.second);

		}
	}
	
}
////////////////////////////////////////////////////////////////////
// updateMove- updating all objects (in window frame viwe) movments,
// movmentMode - set by the player, side2move too.
// removing all dead objects from the graph.
// set to info-bar position.
////////////////////////////////////////////////////////////////////
void ViewStation::updateMove(Movments movmentMode, Movments side2move)
{

	m_astronaut->setMove(movmentMode, side2move);
	m_astronaut->updateMove();
	for (auto &i : m_movableVec)
		if (m_windowRec.intersects(i->getGlobalBounds()) || i->wasBorn())
		{
			i->setWasBorn(true);
			i->updateMove();
		}

	m_graph.erase(std::remove_if(m_graph.begin(), m_graph.end(),
		[](const gamePairType &go) {return !go.second->isAlive(); }), m_graph.end());

	m_info->setPosition(m_astronaut->getPosition() - V2f{ 480, 500 });
	
	ManageTrais::updateMove();
}
////////////////////////////////////////////////////////////////////
// addShot - adding shot of the astronaut. any shot will be 
// terminated in 3 second if it did not hit any thing.
////////////////////////////////////////////////////////////////////
void ViewStation::addShot(Movments side2move)
{
	auto shotPos = sf::Vector2f{ m_astronaut->getPosition().x, m_astronaut->getPosition().y + 40 };
	auto shot = std::make_pair(4, std::make_shared<Shot>(V2f{1,1} , shotPos, side2move));
	shot.second->setWasBorn(true);
	m_sound.playLaserGun();
	m_graph.push_back(shot);
	m_movableVec.push_back(shot.second);
}
////////////////////////////////////////////////////////////////////
//finishLevel- return if the astrunaut came to his spaceShipe
////////////////////////////////////////////////////////////////////
bool ViewStation::finishLevel()
{
	 return m_astronaut->didComeToShip(); 
}
////////////////////////////////////////////////////////////////////
//getScore - return the score
////////////////////////////////////////////////////////////////////
int ViewStation::getScore()
{
	return m_info->getScore(); 
}
////////////////////////////////////////////////////////////////////
// getViewPosition- return the center of view
////////////////////////////////////////////////////////////////////
sf::Vector2f ViewStation::getViewPosition() const
{
	return m_view.getCenter(); 
}



///////////////////////////////////////////////////////////////////
// getNewObj
////////////////////////////////////////////////////////////////////

std::pair<size_t, std::shared_ptr<GameObject>> ViewStation::getNewObj(std::string name, size_t printLevel, V2f s, V2f p)
{
	return std::make_pair(printLevel, Factory::create(name, s, p));
}
///////////////////////////////////////////////////////////////////
// astroSetMove
////////////////////////////////////////////////////////////////////
void ViewStation::astroSetMove(Movments move, Movments side2move)
{
	m_astronaut->setMove(move, side2move);
}


/////////////////////////////////////////////////////////////////////
//loadGameObjects()
//////////////////////////////////////////////////////////////////////
void ViewStation::loadGameObjects()
{

	updateCharsMap();
	m_graph.clear();
	m_movableVec.clear();
	std::string line;

	if (!m_theFile.is_open()) return;
	
		getline(m_theFile, line);	//Read a line.
		m_rowsNum = atoi(line.c_str()); //reads the number of rows
		getline(m_theFile, line);
		m_colsNum = atoi(line.c_str());  //reads the number of columns

		for (int i = 0; i < m_rowsNum; i++)
		{
			getline(m_theFile, line);
			for (int j = 0; j < line.size() ; j++)
			{
				auto newObj = m_charsMap.find(line[j]);
				if (newObj == m_charsMap.end())
					continue;
				    //acitvate the c-tor of the right object:
					newObj->second(V2f{float( j),float(i) });
			}
			m_theFile.get();
		}
	
	
}
//////////////////////////////////////////////////////////////////////////
// 'H'=alian, 'A'=astroid, 'F'=fruit, 'R'=rock, 'r'= big rock /-/ index 3
// 't'=tree, 'T'= big tree   /-/  index 2
// 'b'=tree, 'n'= big tree   /-/  index 5
// '&'= tree +rock, '*'= rock + tree /-/ index 1-2, 2-1
// '7'= tree +rock, '8'= rock + tree /-/ index 4-5, 5-4
//  Q= Astronaut
//  S=SpaceShipe
////////////////////////////////////////////////////////////////////////////
void ViewStation::updateCharsMap()
{
	const float RX = 50;
	/*static bool updated = false;
	if (updated) return;*/
	m_charsMap['H'] = [&](V2f & p) { auto obj = getNewObj("Alien", 3, V2f{ .12f,.15f }, V2f{ p.x * 45 - 600 ,p.y * 55 - 41 }); m_graph.push_back(obj);	m_movableVec.push_back(obj.second);	};
	m_charsMap['S'] = [&](V2f & p) { auto obj = getNewObj("SpaceShip", 5, V2f{ 0.7f,0.7f }, V2f{ p.x * 45 - 600 , p.y * 55 }); m_graph.push_back(obj); m_movableVec.push_back(obj.second);	};
	m_charsMap['A'] = [&](V2f & p) { auto obj = getNewObj("Astroid", 4, V2f{ 1,1 }, V2f{ p.x * 45 - 600 , p.y * 55 }); m_graph.push_back(obj); m_movableVec.push_back(obj.second);	};
	m_charsMap['F'] = [&](V2f & p) { auto obj = getNewObj("Fruit", 3, V2f{ 0.15f,0.15f }, V2f{ p.x * 45 - 590 , p.y * 55 + 20 });  m_graph.push_back(obj);	 m_movableVec.push_back(obj.second);  };
	m_charsMap['R'] = [&](V2f & p) { auto obj = getNewObj("Rock", 3, V2f{ 0.2f,0.2f }, V2f{ p.x * 45 - 600 , p.y * 55 }); obj.second->setWasBorn(true); m_graph.push_back(obj);  m_movableVec.push_back(obj.second);  };
	m_charsMap['@'] = [&](V2f & p) { auto obj = getNewObj("Rock", 3, V2f{ 0.2f,0.2f }, V2f{ p.x * 45 - 600 , p.y * 55 });  m_graph.push_back(obj);  m_movableVec.push_back(obj.second);  };
	m_charsMap['r'] = [&](V2f & p) { auto obj = getNewObj("Rock", 3, V2f{ 0.3f,0.3f }, V2f{ p.x * 45 - 600 , p.y * 55 });	m_graph.push_back(obj);  };
	m_charsMap['t'] = [&](V2f & p) { auto obj = getNewObj("Tree", 2, V2f{ 0.5f,0.5f }, V2f{ p.x * 45 - 600 , p.y * 55 - 150 });	m_graph.push_back(obj); };
	m_charsMap['T'] = [&](V2f & p) { auto obj = getNewObj("Tree", 2, V2f{ 1,1 }, V2f{ p.x * 45 - 600, p.y * 55 - 350 });	m_graph.push_back(obj);	  };
	m_charsMap['b'] = [&](V2f & p) { auto obj = getNewObj("Tree", 5, V2f{ 0.5f,0.5f }, V2f{ p.x * 45 - 600 , p.y * 55 - 150 }); m_graph.push_back(obj); };
	m_charsMap['n'] = [&](V2f & p) { auto obj = getNewObj("Tree", 5, V2f{ 1,1 }, V2f{ p.x * 45 - 600, p.y * 55 - 350 }); m_graph.push_back(obj); };
	m_charsMap['&'] = [&](V2f & p) { auto obj = getNewObj("Tree", 1, V2f{ 1,1 }, V2f{ p.x * 45 - 600, p.y * 55 - 350 }); m_graph.push_back(obj);
					                auto obj2 = getNewObj("Rock", 3, V2f{ 0.2f,0.2f }, V2f{ p.x * 45 - 600 , p.y * 55 }); m_graph.push_back(obj2);	};
	m_charsMap['*'] = [&](V2f & p) { auto obj = getNewObj("Tree", 2, V2f{ 1,1 }, V2f{ p.x * 45 - 600, p.y * 55 - 350 }); 	m_graph.push_back(obj);
	                                auto obj2 = getNewObj("Rock", 3, V2f{ 0.2f,0.2f }, V2f{ p.x * 45 - 600 , p.y * 55 }); m_graph.push_back(obj2); };
	m_charsMap['7'] = [&](V2f & p) { auto obj = getNewObj("Tree", 4, V2f{ 1,1 }, V2f{ p.x * 45 - 600, p.y * 55 - 350 });  m_graph.push_back(obj);
	                                auto obj2 = getNewObj("Rock", 5, V2f{ 0.2f,0.2f }, V2f{ p.x * 45 - 600 , p.y * 55 }); m_graph.push_back(obj2); };
	m_charsMap['8'] = [&](V2f & p) { auto obj = getNewObj("Tree", 5, V2f{ 1,1 }, V2f{ p.x * 45 - 600, p.y * 55 - 350 });	m_graph.push_back(obj);
	                                auto obj2 = getNewObj("Rock", 4, V2f{ 0.2f,0.2f }, V2f{ p.x * 45 - 600 , p.y * 55 }); m_graph.push_back(obj2);};

	
	/*updated = true;*/
}