#pragma once
#include "Character.h"
#include <iostream>

class Player : public Character
{
	bool m_HasKey;
public:
	Player(float health, int x, int y)
		: Character(health, x, y)
		, m_HasKey(false)
	{
		//
	}

	void Draw()
	{
		std::cout << "@" << std::endl;
	}

	void OutputInfo()
	{
		std::cout << "Health: " << m_Health << std::endl;
		std::cout << "X: " << m_Position.x << std::endl;
		std::cout << "Y: " << m_Position.y << std::endl;
		std::cout << "Has Key: " << (m_HasKey ? "true" : "false") << std::endl;
		Draw();
	}

	void UseHealth(float health)
	{
		m_Health += health;

		if (!m_IsAlive)
		{
			m_IsAlive = true;
		}
	}

	void PickupKey()
	{
		m_HasKey = true;
	}
};