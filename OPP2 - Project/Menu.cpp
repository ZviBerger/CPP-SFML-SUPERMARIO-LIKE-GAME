#include "Menu.h"




Menu::Menu(sf::Texture &texture, sf::Vector2f position, sf::Vector2f size, sf::RenderWindow &myWindow)
	:GameManage(texture, position, size), m_window(myWindow)
{
	m_menuTxt.loadFromFile(path2image::menu);
	m_background.setTexture(&m_menuTxt);
	m_background.setPosition(position);
	m_background.setSize(size);
	for (int index = 0; index < m_buttNum; index++)
	{
		m_buttons.push_back(sf::RectangleShape(sf::Vector2f{ 500.27f ,79.35f  }));
		m_buttons[index].setFillColor(sf::Color::Color(1, 1, 1, 0));

	}
	
	int i = 0; 
	for(auto Ypos : std::vector<float>{ 242 ,351 ,453 })
	m_buttons[i++].setPosition(sf::Vector2f{ 390,Ypos });
	

}

/////////////////////////////////////////////////////////////////
//  newGame
/////////////////////////////////////////////////////////////////
bool Menu::newGame()
{
	m_window.setFramerateLimit(40);
	m_window.setSize(sf::Vector2u(unsigned int(windowSize.x), unsigned int(windowSize.y)));

	while (m_window.isOpen())
	{
		m_timer += 0.05f;

		if (handleEvent()) //finish and start the g
		{
			m_window.setFramerateLimit(60);
			return true;
		}
		for (int i = 0; i < 3; i++)
		{
			if (i == m_buttIndex)
				m_buttons[i].setFillColor(sf::Color::Color(0,0,0,sf::Uint8(abs(sin(m_timer))* 120)));
			else
				m_buttons[i].setFillColor(sf::Color::Color(0, 0, 0, 0));
		}
		m_window.clear();
		m_window.draw(m_background);
		m_window.draw(m_buttons[m_buttIndex]);
		m_window.display(); 
		
	}


	return false;
}
/////////////////////////////////////////////////////////////////
//  show an other window
/////////////////////////////////////////////////////////////////
void Menu::showOtherWindow(const WindowButton &button, std::string path2image, const sf::Vector2f &winSize)
{
	sf::Texture texture;
	sf::RectangleShape winButton(button._size);
	sf::RectangleShape background(winSize);
	sf::Color defColor(sf::Color::Color(0, 0, 0, 0));
	bool onTheButton = false;
	texture.loadFromFile(path2image);
	background.setTexture(&texture);
	winButton.setFillColor(defColor);
	winButton.setPosition(button._position);

	while (m_window.isOpen())
	{
		for (sf::Event event; m_window.pollEvent(event)&& m_window.isOpen();)
		{
			
			switch (event.type)
			{
			case  sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseMoved:
				if (winButton.getGlobalBounds().contains(sf::Vector2f{ float(event.mouseMove.x),float(event.mouseMove.y) }))
				{
					onTheButton = true;
					winButton.setFillColor(button._presetColor);
				}
				else
				{
					winButton.setFillColor(defColor);
					onTheButton = false;
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (onTheButton)
					return;
				break;
			default:
				break;
			}
		}
		m_window.clear();
		m_window.draw(background);
		m_window.draw(winButton);
		m_window.display();
	}
}
/////////////////////////////////////////////////////////////////
//  handle Event
/////////////////////////////////////////////////////////////////
bool Menu::handleEvent()
{
	for (sf::Event event; m_window.pollEvent(event)&&m_window.isOpen();)
	{
		sf::Vector2f crds{ float(event.mouseMove.x),float(event.mouseMove.y) };
		switch (event.type)
		{
		case  sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::MouseMoved:
		{
			for (int i = 0; i < m_buttNum; i++)
				if (m_buttons[i].getGlobalBounds().contains(crds) && m_buttIndex != i)
				{
					m_buttIndex = i;
					m_timer = 0;
				}
			break;

		}

		case sf::Event::MouseButtonPressed:
		{
			if (buttenPreset()) return true;

		}
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				if (m_buttIndex > 0)  m_buttIndex--, m_timer = 0;
				break;
			case sf::Keyboard::Down:
				if (m_buttIndex < m_buttNum - 1)  m_buttIndex++, m_timer = 0;
				break;
			case sf::Keyboard::Return:

				if (buttenPreset())  return true;
				break;
			default:
				break;
			}
		default:
			break;
		}

	}

	return false;
}
/////////////////////////////////////////////////////////////////
//  buttenPreset
/////////////////////////////////////////////////////////////////
bool Menu::buttenPreset()
{
	switch (m_buttIndex)
	{
	case 0:
		return true;  //the NEW GAME button  pressed
	case 1:
		showHelp();
		break;
	case 2:
		m_window.close();
		break;

	}
	return false;
}
/////////////////////////////////////////////////////////////////
//  showHelp
/////////////////////////////////////////////////////////////////
void Menu::showHelp()
{

	WindowButton butten;
	butten._position = sf::Vector2f{ 28,19 };
	butten._size = sf::Vector2f{ 178, 60 };
	butten._presetColor = sf::Color::Color(0,0,0,50);

	showOtherWindow(butten,path2image::help, windowSize);
	m_timer = 0;
}

////////////////////////////////////////////////////////////////
// next level
/////////////////////////////////////////////////////////////////
void Menu::nextLevel()
{
	WindowButton butten;
	butten._position = sf::Vector2f{ 365.5,378 };
	butten._size = sf::Vector2f{ 470.27f,64.35f };
	butten._presetColor = sf::Color::Color(0,0,0, 50);

	showOtherWindow(butten, path2image::nextLevel, windowSize);

}