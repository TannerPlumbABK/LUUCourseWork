#pragma once

#include "Point.h"
#include <iostream>

class Character
{
protected:
	float m_Health;
	Point<int> m_Position;
	bool m_IsAlive;
public:
	Character(float health, int x, int y)
		: m_Health(health)
		, m_IsAlive(false)
	{
		m_Position.x = x;
		m_Position.y = y;
	}

	int GetHealth()
	{
		return m_Health;
	}

	int GetPositionX()
	{
		return m_Position.x;
	}

	int GetPositionY()
	{
		return m_Position.y;
	}

	virtual void Draw() = 0;
	virtual void OutputInfo() = 0;

	void Move(int x, int y)
	{
		m_Position.x += x;
		m_Position.y += y;
	}

	void TakeDamage(float damage)
	{
		if (m_IsAlive)
		{
			m_Health -= damage;

			if (m_Health <= 0)
			{
				m_Health = 0;
				m_IsAlive = false;
			}
		}
	}
};