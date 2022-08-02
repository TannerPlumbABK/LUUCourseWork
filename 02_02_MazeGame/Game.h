#pragma once

#include "Player.h"
#include "Level.h"
#include "Shop.h"

constexpr int maxLevel = 3;
constexpr int levelCompleteMoneyReward = 25;
constexpr int startingShopOdds = 0;
constexpr int increasingOddsPerLevel = 100;

class Game
{
private:
	Player m_player;
	Level m_level;
	Shop m_shop;
	bool m_isGameOver;
	bool m_userQuit;
	int m_currentLevelNum;
	int m_shopOdds;

	bool Update();
	void Draw();
	bool HandleCollision(int newPlayerX, int newPlayerY);
	bool ProcessInput();

public:
	Game();

	bool Load(int levelNum);
	void Run();

	bool IsGameOver();
	bool DidUserQuit();

	int GetPlayerLives();

	void DisplayHUD();
};

