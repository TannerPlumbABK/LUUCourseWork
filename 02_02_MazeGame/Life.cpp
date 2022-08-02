#include <iostream>
#include <Windows.h>

#include "Life.h"
#include "AudioManager.h"
#include "Player.h"

Life::Life(int x, int y, ActorColor color)
	: PlacableActor(x, y, color)
{
	//
}

ActorType Life::GetType()
{
	return ActorType::Life;
}

void Life::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);
	std::cout << (char)3;
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}

void Life::HandleCollision(PlacableActor& player)
{
	Remove();
	player.SetPosition(GetPositionX(), GetPositionY());
	dynamic_cast<Player*>(&player)->AddLives(1);
	AudioManager::GetInstance()->PlayLifePickupSound();
}