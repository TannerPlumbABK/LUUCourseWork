#include "Character.h"

Character::Character(float health, int x, int y)
	: m_Health(health)
	, m_IsAlive(false)
{
	m_Position.x = x;
	m_Position.y = y;
}

int Character::GetHealth()
{
	return m_Health;
}

int Character::GetPositionX()
{
	return m_Position.x;
}

int Character::GetPositionY()
{
	return m_Position.y;
}

void Character::Move(int x, int y)
{
	m_Position.x += x;
	m_Position.y += y;
}

void Character::TakeDamage(float damage)
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