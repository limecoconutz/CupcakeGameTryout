#include "Cupcakes.h"
#include "Player.h"
#include <random>


using namespace sf;
Cupcakes::Cupcakes()
	:m_maxCupcakes(5)
{
	std::random_device r;
	std::default_random_engine e(r());
	std::uniform_int_distribution<int>uniform_dist(8, 9);

	//Randomize cupcake speed
	m_cupcakeSpeed = uniform_dist(e);
	
}

Cupcakes::~Cupcakes() = default;

void Cupcakes::update(sf::RenderWindow& w)
{
	const double dt = m_timer.Mark();

	//Update and reset the timer for spawning cupcakes and moving them
	m_cupcakeSpawnTimer += dt;

	//Update the cupcakes as per last frame
	removeCupcake();

	//spawn and move cupcakes
		if (m_cupcakeSpawnTimer > 50.0f)
		{ //one second passed
			spawn();
			move();
			m_cupcakeSpawnTimer = 0.f;
		}
		else
		{//Give a cooldown between timer resets
			m_cupcakeSpawnTimer += 0.4f;
		}

}



void Cupcakes::spawn()
{  
	Sprite m_cupcakeSprite;
	//Set cupcake sprites origin point to be at the center 
	m_cupcakeSprite.setOrigin(sf::Vector2f(25.f, 25.f));

	//Randomize cupcake type
	int const type = rand() % 3;
	

	if (m_spriteVector.size() < m_maxCupcakes)
	{
		switch (type)
		{
		case 0:
			makeCupcake("Images/Cupcake1.png", 0.2f, m_cupcakeSprite);
			break;

		case 1:
			makeCupcake("Images/Cupcake2.png", 0.2f, m_cupcakeSprite);
			break;

		case 2:
			makeCupcake("Images/Cupcake3.png", 0.1f, m_cupcakeSprite);
			break;
		}

	}
	else
	{
		m_maxCupcakes += 0.1;
	}

}


void Cupcakes::move()
{

	for (Sprite& sprite: m_spriteVector)
	{
		//Move the cupcakes down
		sprite.move(0.f, m_cupcakeSpeed);
	}

}


void Cupcakes::draw(sf::RenderWindow& window)
{
	for (Sprite& sprite : m_spriteVector)
	{
		window.draw(sprite);
	}

}

void Cupcakes::removeCupcake()
{
	
	m_spriteVector.erase(
		std::remove_if(
			m_spriteVector.begin(),
			m_spriteVector.end(),
			[=](const sf::Sprite& s) { return s.getGlobalBounds().top >= m_screenHeight; }
	), m_spriteVector.end());
	
	/*for (int i = 0; i < m_spriteVector.size(); i++)
	{
		if (m_spriteVector[i].getGlobalBounds().top > m_screenHeight)
		{
			m_spriteVector.erase(m_spriteVector.begin() + i);
			i--;
		}
	}*/
}

void Cupcakes::makeCupcake(std::string textureLocation, float scale, Sprite cupcakeSprite)
{
	float const x = (rand() % m_screenWidth);
	cupcakeSprite = Sprite(TextureHolder::GetTexture(textureLocation));
	cupcakeSprite.setScale(scale, scale);
	cupcakeSprite.setPosition(x, 0.f);
	m_spriteVector.push_back(cupcakeSprite);

}
