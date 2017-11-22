#pragma once
#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib,  "sfml-audio-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib,  "sfml-audio.lib")
#else
#error "Unrecognized configuration!"
#endif

#include <SFML/Graphics.hpp>
#include "ViewStation.h"
#include "Menu.h"
#include "Utilities.h"
class Controller
{
public:
	Controller(); 
	~Controller();
	void startGame(std::string levelPathFile);
private:
	
	std::unique_ptr<ViewStation> m_graphView;
	std::unique_ptr<Menu> m_menu;
	std::vector<std::string> m_level;
	sf::RenderWindow m_window;
	Movments m_movmentMode;
	Movments m_side2move;
	int m_totalScore = 0;
	void setLevel(std::string levelsPathFile);
	bool runLevel(const unsigned int  & Mylevel);
	void handleEvents(sf::Event& event);
	void betweenLevelsPrint();
	bool finishLevel();
	bool gameOverPrint();
	
};

