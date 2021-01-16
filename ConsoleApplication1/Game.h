#pragma once

#include "GameEngine.h"
#include "FrameTimer.h"

class Game
{
public:
	//Constructor
	Game();
	//run all the private functions
	void run();

private:
	//The usual RenderWindow
	sf::RenderWindow m_Window;

	//What are the screen height and width? (to be used in spawn() and update())
	unsigned int m_heightOfScreen = sf::VideoMode::getDesktopMode().height;
	unsigned int m_widthOfScreen = sf::VideoMode::getDesktopMode().width;

	//How many seconds, in gametime, have passed?
	FrameTimer ft;
	const float m_dt = ft.Mark();

	//Is the game currently playing?
	bool m_Playing = true;

	//How much time has passed in-game?
	sf::Time m_GameTimeTotal;

	//Where is the mouse on the screen?
	sf::Vector2i m_mousePosition_Window;
	sf::Vector2f m_mousePosition;
	sf::FloatRect m_mouseRect;



};

