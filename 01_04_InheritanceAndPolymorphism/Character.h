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
	Character(float health, int x, int y);

	int GetHealth();
	int GetPositionX();
	int GetPositionY();

	virtual void Draw() = 0;
	virtual void OutputInfo() = 0;

	void Move(int x, int y);
	void TakeDamage(float damage);
};