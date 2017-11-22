#include "Controller.h"
TextBox t{ "debuging",V2f(1,1) };
/////////////////////////////////////////////////////////////////////////////////////
// Ctor
/////////////////////////////////////////////////////////////////////////////////////

Controller::Controller()
{
	srand(unsigned( time(0)));
	m_window.create(sf::VideoMode{unsigned int(windowSize.x),unsigned int(windowSize.y) }, "The Moon Survivor", 5);
	m_window.setFramerateLimit(60);
	
}


Controller::~Controller()
{
}
/////////////////////////////////////////////////////////////////////////////////////
//startGame
/////////////////////////////////////////////////////////////////////////////////////

void Controller::startGame(std::string levelPathFile)
{
	setLevel(levelPathFile);
	
	m_menu = std::make_unique<Menu>(sf::Texture{}, V2f{ 0,0 }, windowSize, m_window);
	bool go2nextLevel = true;
	while (m_window.isOpen()&& m_menu->newGame() )
	{

			for (unsigned level = 0; level < m_level.size() && go2nextLevel  ; level++)
			//for any level call runLevel function
				go2nextLevel = runLevel(level);

	}
}

/////////////////////////////////////////////////////////////////////////////////////
//setLevel
//Read from Levels.txt the other files names
/////////////////////////////////////////////////////////////////////////////////////
void Controller::setLevel(std::string levelsPathFile)
{
	std::ifstream stream(levelsPathFile);
	std::string level;
	while (getline(stream, level))
		m_level.push_back(level);
	stream.close();

	
}

/////////////////////////////////////////////////////////////////////////////////////
//Gets number of level, sets in board and runs the game
//The engine of the game - for any iteration do 3 basic thing:
//1. check collutions 2.update+events 3.draw the objects
/////////////////////////////////////////////////////////////////////////////////////
bool Controller::runLevel(const unsigned int & levelInd)
{
	if (levelInd >= m_level.size())
		return false;

	m_window.clear();
	m_graphView.get();
	m_graphView = std::make_unique<ViewStation>(m_level[levelInd], levelInd+1);
	m_graphView->drawView(m_window);
	sf::Event event;

	while (m_window.isOpen())
	{
		m_movmentMode = FALL;
		m_graphView->checkCollide();
		m_window.pollEvent(event);
		handleEvents(event);
		
		m_graphView->updateMove(m_movmentMode, m_side2move);
		m_graphView->drawView(m_window);
		m_window.display();

		if ( m_graphView->finishLevel())
			return finishLevel();  //true
		if( m_graphView->isGameOver())
			return gameOverPrint(); //false
	}

	return false;
		

}
/////////////////////////////////////////////////////////////////////////////////////
//handleEvents
/////////////////////////////////////////////////////////////////////////////////////
void Controller::handleEvents(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_graphView->astroSetMove(GO, RIGHT);
		m_side2move = RIGHT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_graphView->astroSetMove(GO, LEFT);
		m_side2move = LEFT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_graphView->astroSetMove(JUMP, m_side2move);
	}
	

	if (event.type == sf::Event::Closed)
		m_window.close();

	switch (event.type)
	{
	case  sf::Event::Closed:
		m_window.close();
		break;
	case sf::Event::KeyPressed:
	{

		switch (event.key.code)
		{
		
		
			case sf::Keyboard::Space:
			{
				m_movmentMode = SHOOT;
				m_graphView->addShot(m_side2move);
				break;
			}
		
			default:
			{
				break;
			}

		}
	}
	
	default:
		
		break;
	}

}
/////////////////////////////////////////////////////////////////////////////////////
//betweenLevelsPrint
/////////////////////////////////////////////////////////////////////////////////////
void Controller::betweenLevelsPrint()
{
	int score = m_graphView->getScore();
	m_totalScore += score;
	TextBox goodLuck{ "Gooood!",  V2f{ m_graphView->getViewPosition().x - float(m_window.getSize().x / 2) + 350, m_graphView->getViewPosition().y - 100 } };
	TextBox youScore{ "Your Score is: " + std::to_string(score) + " "
		+ "\nTotal Score In Game: " + std::to_string(m_totalScore),
		V2f{ m_graphView->getViewPosition().x - float(m_window.getSize().x / 2) + 350, m_graphView->getViewPosition().y  } };
	goodLuck.editCharSize(80);
	sf::Clock clock;

	goodLuck.draw(m_window);
	youScore.draw(m_window);
	m_window.display();
	while (int(clock.getElapsedTime().asSeconds()) < 8);
}
/////////////////////////////////////////////////////////////////////////////////////
//finishLevel
/////////////////////////////////////////////////////////////////////////////////////

bool Controller::finishLevel()
{
	sf::Clock clock;
	while (clock.getElapsedTime().asSeconds() < 5) 
	{
		m_movmentMode = FALL;
		m_graphView->checkCollide();
		m_graphView->updateMove(m_movmentMode, m_side2move);
		m_graphView->drawView(m_window);
		m_window.display();
	}

	betweenLevelsPrint();
	sf::View v{ V2f{ windowSize.x / 2,windowSize.y / 2 },windowSize };
	m_window.setView(v);
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////
//gameOverPrint
/////////////////////////////////////////////////////////////////////////////////////
bool Controller::gameOverPrint()
{
	int score = m_graphView->getScore();
	TextBox gemeOver{ "Game Over", V2f{ m_graphView->getViewPosition().x - float(m_window.getSize().x /2) + 350, m_graphView->getViewPosition().y - 100 } };
	TextBox	youScore{ "your score is: " + std::to_string(score) + " !" , V2f{ m_graphView->getViewPosition().x - float(m_window.getSize().x / 2) +350,  m_graphView->getViewPosition().y} };
	gemeOver.editCharSize(80);
	sf::Clock clock;
	gemeOver.draw(m_window);
	youScore.draw(m_window);
	m_window.display();
	while (int(clock.getElapsedTime().asSeconds()) < 10);
	sf::View v{ V2f{ windowSize.x / 2,windowSize.y / 2 },windowSize };
	m_window.setView(v);
	return false;
}
