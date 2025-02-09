#pragma once
#include <thread>

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

	int m_initialDraw;

	bool runThread;
	bool isThreadRunning;
	bool skipThread;
	std::thread* drawThread;

	bool Update();
	void Draw();
	void RedrawPlayer();
	void RedrawEnemies();
	void RedrawActors();
	bool CheckCollision(int newPlayerX, int newPlayerY);
	bool ProcessInput();
	void DrawThread();
	bool ResetGame();
	void KillThread();

public:
	Game();

	bool Load(int levelNum);
	void Run();

	bool IsGameOver();
	bool DidUserQuit();

	int GetPlayerLives();

	void DisplayHUD();
};
