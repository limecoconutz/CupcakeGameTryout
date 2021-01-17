#include "Game.h"
#include "TextureHolder.h"

using namespace sf;

TextureHolder th;

Game::Game()
{
	//Get the screen resolution and create an SFML window and fullscreen view
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width / 2;
	resolution.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(resolution.x, resolution.y), "Catch all the Cupcakes game!!!", Style::Default);
	//m_Window.setFramerateLimit(60);
}

void Game::run()
{
	GameEngine m_gameEngine(m_Window);

	//Timing
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();
		//Update the total game time
		m_GameTimeTotal += dt;
		
		m_mousePosition_Window = sf::Mouse::getPosition(m_Window);
		m_mousePosition = m_Window.mapPixelToCoords(m_mousePosition_Window);

		m_gameEngine.update(static_cast<unsigned int>(dt.asMilliseconds()), m_mousePosition, sf::Mouse::isButtonPressed(Mouse::Left));

		//Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_Window.close();
		}
	}
}
