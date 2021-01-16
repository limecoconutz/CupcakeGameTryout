#include "GameEngine.h"
#include "Player.h"

#include <random>
#include <SFML/Graphics.hpp>


using namespace sf;
GameEngine::GameEngine(sf::RenderWindow& window)
	:m_Window(window)
	,m_maxCupcakes(5)
{
	//Associate the sprite with the texture and set the position to render
	m_BackgroundSprite = Sprite(TextureHolder::GetTexture("Images/background.png"));
	m_BackgroundSprite.setPosition(0, 0);
}

GameEngine::~GameEngine() = default;

void GameEngine::update(unsigned int dt, sf::Vector2f mousePosition, bool isButtonPressed)
{
	updateCupcakesPosition(dt);

	//Update the cupcakes as per last frame
	removeOffscreenCupcakes();

	if (isButtonPressed) {
		checkForCupcakeHits(mousePosition);
	}

	//Update and reset the timer for spawning cupcakes and moving them
	m_cupcakeSpawnTimer += dt;
	if (m_cupcakeSpawnTimer > m_cupcakeSpawnTimerMax)
	{ //one second passed
		spawnNewCupcake();
		m_cupcakeSpawnTimer = 0.f;
	}
	else
	{//Give a cooldown between timer resets
		m_cupcakeSpawnTimer += 0.4f;
	}

	draw();
}



void GameEngine::draw()
{
	//Clear the last frame
	m_Window.clear(Color::Cyan);

	//Draw the background
	m_Window.draw(m_BackgroundSprite);

	//Spawn and draw the cupcakes
	for (Cupcake& cupcake : m_Cupcakes)
	{
		m_Window.draw(cupcake.sprite);
	}

	m_Window.display();
}




void GameEngine::checkForCupcakeHits(sf::Vector2f mousePosition) {
	for (int c = 0; c < m_Cupcakes.size(); c++)
	{
		//if the cupcake is clicked on
		if (m_Cupcakes[c].sprite.getGlobalBounds().contains(mousePosition))
		{
			//increase player points
			player.increasePoints();
			//print-out points for testing purposes
			std::cout << "Points: " << player.getPoints() << "\n";

			//delete cupcake sprite
			m_Cupcakes.erase(m_Cupcakes.begin() + c);
		}
	}
}



void GameEngine::spawnNewCupcake()
{  
	if (m_Cupcakes.size() < m_maxCupcakes)
	{
		Cupcake cupcake;
		cupcake.create(m_Window);
		m_Cupcakes.push_back(cupcake);
	}
	else
	{
		m_maxCupcakes += 0.1;
	}

}

void GameEngine::updateCupcakesPosition(unsigned int dt)
{
	for (Cupcake& cupcake : m_Cupcakes)
	{
		//Move the cupcakes down
		cupcake.sprite.move(0.f, cupcake.speed * dt / 1000);
	}
}

void GameEngine::removeOffscreenCupcakes()
{
	std::for_each(
		m_Cupcakes.begin(),
		m_Cupcakes.end(),
		[&](const Cupcake& cupcake) 
		{ 
			if (cupcake.sprite.getGlobalBounds().top >= m_Window.getSize().y) {
				//decrease player health
				player.decreaseHealth();
				//print-out health for testing purposes
				std::cout << "Health: " << player.getHealth() << "\n";
			}
		});

	m_Cupcakes.erase(
		std::remove_if(
			m_Cupcakes.begin(),
			m_Cupcakes.end(),
			[&](const Cupcake& cupcake) { return cupcake.sprite.getGlobalBounds().top >= m_Window.getSize().y; }
	), m_Cupcakes.end());

	
}

