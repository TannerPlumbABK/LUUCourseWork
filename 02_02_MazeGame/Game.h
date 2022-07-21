#pragma once

#include <iostream>
#include <conio.h>
#include <Windows.h>

#include "Player.h"
#include "Level.h"

class Game
{
	Player m_player;
	Level m_level;
	bool m_isGameOver;

public:
	Game();
	~Game();

	bool Load();
	void Run();

	bool IsGameOver() { return m_isGameOver; }

private:
	bool Update();
	void Draw();
};

