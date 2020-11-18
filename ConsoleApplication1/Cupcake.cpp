#include "Cupcake.h"
#include "Player.h"
#include <random>


using namespace sf;
Cupcake::Cupcake()
{
	std::random_device r;
	std::default_random_engine e(r());
	std::uniform_int_distribution<int>uniform_dist(8, 9);
	
	m_deleted = false;

	//Randomize cupcake speed
	m_cupcakeSpeed = uniform_dist(e);
	m_maxCupcakes = 5;
}

Cupcake::~Cupcake() = default;

void Cupcake::update(sf::RenderWindow& w)
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



void Cupcake::spawn()
{  
	//Set cupcake sprites origin point to be at the center 
	m_cupcakeSprite.setOrigin(sf::Vector2f(25.f, 25.f));

	//Randomize cupcake type
	int type = rand() % 3;
	float x = (rand() % m_screenWidth);

	if (m_spriteVector.size() < m_maxCupcakes)
	{
		switch (type)
		{
		case 0:
			m_cupcakeSprite = Sprite(TextureHolder::GetTexture("Images/Cupcake1.png"));
			m_cupcakeSprite.setScale(0.2f, 0.2f);
			m_cupcakeSprite.setPosition(x, 0.f);
			m_spriteVector.push_back(m_cupcakeSprite);
			break;

		case 1:
			m_cupcakeSprite = Sprite(TextureHolder::GetTexture("Images/Cupcake2.png"));
			m_cupcakeSprite.setScale(0.2f, 0.2f);
			m_cupcakeSprite.setPosition(x, 0.f);
			m_spriteVector.push_back(m_cupcakeSprite);
			break;

		case 2:
			m_cupcakeSprite = Sprite(TextureHolder::GetTexture("Images/Cupcake3.png"));
			m_cupcakeSprite.setScale(0.1f, 0.1f);
			m_cupcakeSprite.setPosition(x, 0.f);
			m_spriteVector.push_back(m_cupcakeSprite);
			break;
		}

	}
	else
	{
		m_maxCupcakes += 0.1;
	}


}


void Cupcake::move()
{

	for (Sprite& sprite: m_spriteVector)
	{
		//Move the cupcakes down
		sprite.move(0.f, m_cupcakeSpeed);
	}

}




void Cupcake::draw(sf::RenderWindow& window)
{
	for (Sprite& sprite : m_spriteVector)
	{
		window.draw(sprite);
	}

}

void Cupcake::removeCupcake()
{
	for (int i = 0; i < m_spriteVector.size(); i++)
	{
		if (m_spriteVector[i].getGlobalBounds().top > m_screenHeight)
		{
			m_spriteVector.erase(m_spriteVector.begin() + i);
			i--;
		}
	}
}
