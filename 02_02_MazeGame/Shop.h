#pragma once

#include "Player.h"

constexpr int increaseOddsPerLevel = 100;

class Shop
{
	int m_shopOdds;
public:
	Shop();

	void LookForShop(Player* player);
	void LoadShop(Player* player);
};

