#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "FrameTimer.h"
#include "Player.h"
#include "TextureHolder.h"

namespace {
	const float MIN_SPEED = 50.0;
	const float MAX_SPEED = 150.0;

	struct Cupcake {
		sf::Sprite sprite;
		double speed;

		void create(sf::RenderWindow& window)
		{
			std::string textureLocation = "";
			float scale = 1.0;

			//Randomize cupcake type
			int const cupcakeType = rand() % 3;
			switch (cupcakeType)
			{
			case 0:
				textureLocation = "Images/Cupcake1.png"; 
				scale = 0.2f;
				break;

			case 1:
				textureLocation = "Images/Cupcake2.png";
				scale = 0.2f;
				break;

			case 2:
				textureLocation = "Images/Cupcake3.png";
				scale = 0.1f;
				break;
			}

			float const x = (rand() % window.getSize().x);
			sprite = sf::Sprite(TextureHolder::GetTexture(textureLocation));
			//Set cupcake sprites origin point to be at the center 
			sprite.setOrigin(sf::Vector2f(25.f, 25.f));
			sprite.setScale(scale, scale);
			sprite.setPosition(x, -sprite.getGlobalBounds().height);

			speed = MIN_SPEED + rand() / (RAND_MAX / (MAX_SPEED - MIN_SPEED));
			std::cout << "New cupcake, speed is " << speed << "\n";
		}
	};
}

class GameEngine
{
public:
	//Constructor - Destructor
	GameEngine(sf::RenderWindow& window);
	~GameEngine();

	/*void interact(sf::Window& w);*/
	void update(unsigned int dt, sf::Vector2f mousePosition, bool isButtonPressed);
	/*void eraseCupcake();*/

private:
	/*
	Private functions (to be used in update() )
	*/

	//Render the game view
	void draw();

	void checkForCupcakeHits(sf::Vector2f mousePosition);
	
	//Create and update the cupcakes
	void spawnNewCupcake();
	void updateCupcakesPosition(unsigned int dt);
	void removeOffscreenCupcakes();

	void makeCupcake(std::string textureLocation, float scale, sf::Sprite cupcakeSprite);
	

	/*
	Private variables
	*/
	sf::RenderWindow& m_Window;

	//Prepare the player
	Player player;

	//Vector of cupcakes
	std::vector<Cupcake> m_Cupcakes;

	//Declare a sprite and a texture for the background
	sf::Sprite m_BackgroundSprite;
	sf::Texture m_BackgroundTexture;

	//What are the screen height and width? (to be used in spawn() and update())
	unsigned int m_screenHeight = sf::VideoMode::getDesktopMode().height;
	unsigned int m_screenWidth = sf::VideoMode::getDesktopMode().width;

	//How far from each other are cupcakes spawning?
	const float m_cupcakeSpawnTimerMax = 80.f;
	float m_cupcakeSpawnTimer = m_cupcakeSpawnTimerMax;

	//What is the maximum number of cupcakes generated?
	double m_maxCupcakes;

	//How fast is the cupcake moving
	float m_cupcakeSpeed;

	//Where is the cupcake?
	sf::FloatRect m_bounds;

	//Counting the time
	FrameTimer m_timer;

};
