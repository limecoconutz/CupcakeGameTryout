#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
using namespace sf;
TextureHolder th;


Engine::Engine()
{
	//Get the screen resolution and create an SFML window and fullscreen view
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(resolution.x, resolution.y), "Catch all the Cupcakes game!!!", Style::Fullscreen);
	//m_Window.setFramerateLimit(60);

	//Associate the sprite with the texture and set the position to render
	m_BackgroundSprite = Sprite(TextureHolder::GetTexture("Images/background.png"));
	m_BackgroundSprite.setPosition(0, 0);

}

void Engine::run()
{
	//Timing
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();
		//Update the total game time
		m_GameTimeTotal += dt;

		//Call each part of the game loop in turn
		input();
		draw();
	}

}


void Engine::draw()
{
	//Clear the last frame
	m_Window.clear(Color::Cyan);

	//Draw the background
	m_Window.draw(m_BackgroundSprite);

	//Spawn and draw the cupcakes
	cupcake.update(m_Window);
	cupcake.draw(m_Window);

	m_Window.display();

}


void Engine::input()
{
	updateMousePosition();

	//Handle the player quitting
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_Window.close();

	}

	////TODO: Handle the player starting the game

	//Handle Mouse clicking
	if (Mouse::isButtonPressed(Mouse::Left) && m_Playing)
	{

		std::vector<sf::Sprite>& cupcakes = cupcake.m_spriteVector;

		for (int c = 0; c < cupcakes.size(); c++)
		{
			//if the cupcake has left the screen
			if (cupcakes[c].getPosition().y >= m_Window.getSize().y)
			{
				//delete the cupcake
				cupcakes.erase(cupcakes.begin() + c);

				//decrease player health
				player.decreaseHealth();
				//print-out health for testing purposes
				std::cout << "Health: " << player.getHealth() << "\n";
			}

			//if the cupcake is clicked on
			if (cupcakes[c].getGlobalBounds().contains(m_mousePosition))
			{
				//increase player points
				player.increasePoints();
				//print-out points for testing purposes
				std::cout << "Points: " << player.getPoints() << "\n";

				//delete cupcake sprite
				cupcakes.erase(cupcakes.begin() + c);
			}
		}
	}
}


void Engine::updateMousePosition()
{
	m_mousePosition_Window = sf::Mouse::getPosition(m_Window);
	m_mousePosition = m_Window.mapPixelToCoords(m_mousePosition_Window);

}