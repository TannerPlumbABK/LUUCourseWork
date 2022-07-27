#pragma once
#include "Character.h"
#include <iostream>

class Enemy : public Character
{
public:
	Enemy(float health, int x, int y);

	void Draw();
	void OutputInfo();
};