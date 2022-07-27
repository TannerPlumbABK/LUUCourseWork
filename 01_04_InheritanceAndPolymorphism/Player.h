#pragma once
#include "Character.h"
#include <iostream>

class Player : public Character
{
	bool m_HasKey;
public:
	Player(float health, int x, int y);

	void Draw();
	void OutputInfo();
	void UseHealth(float health);
	void PickupKey();
};