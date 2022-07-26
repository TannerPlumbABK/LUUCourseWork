#pragma once

#include <string>

#include "Player.h"
#include "Level.h"

class Game
{
private:
	Player m_player;
	Level m_level;
	bool m_isGameOver;
	bool m_userQuit;

	bool Update();
	void Draw();
	bool HandleCollision(int newPlayerX, int newPlayerY);

public:
	Game();
	~Game();

	bool Load(std::string levelName);
	void Run();

	bool IsGameOver() { return m_isGameOver; }
	bool DidUserQuit() { return m_userQuit; }

	int GetPlayerLives() { return m_player.GetLives(); }
};

