#pragma once
#include "Character.h"
#include <iostream>

class Enemy : public Character
{
public:
	Enemy(float health, int x, int y)
		: Character(health, x, y)
	{
		//
	}

	void Draw()
	{
		std::cout << "*" << std::endl;
	}

	void OutputInfo()
	{
		std::cout << "Health: " << m_Health << std::endl;
		std::cout << "X: " << m_Position.x << std::endl;
		std::cout << "Y: " << m_Position.y << std::endl;
		Draw();
	}
};