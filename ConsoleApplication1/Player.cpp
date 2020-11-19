#include "Player.h"
#include "TextureHolder.h"

using namespace sf;

Player::Player()
	:m_points(0), m_health(0), m_dead(false)
{

}

Player::~Player() = default;

bool Player::isAlive()
{
	return m_health > 0;
}
