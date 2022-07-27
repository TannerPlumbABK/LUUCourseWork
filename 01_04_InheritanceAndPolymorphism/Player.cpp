#include "Player.h"

Player::Player(float health, int x, int y)
	: Character(health, x, y)
	, m_HasKey(false)
{
	//
}

void Player::Draw()
{
	std::cout << "@" << std::endl;
}

void Player::OutputInfo()
{
	std::cout << "Health: " << m_Health << std::endl;
	std::cout << "X: " << m_Position.x << std::endl;
	std::cout << "Y: " << m_Position.y << std::endl;
	std::cout << "Has Key: " << (m_HasKey ? "true" : "false") << std::endl;
	Draw();
}

void Player::UseHealth(float health)
{
	m_Health += health;

	if (!m_IsAlive)
	{
		m_IsAlive = true;
	}
}

void Player::PickupKey()
{
	m_HasKey = true;
}