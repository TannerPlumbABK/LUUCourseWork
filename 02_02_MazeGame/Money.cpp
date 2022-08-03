#include <iostream>
#include <Windows.h>
#include <chrono>

#include "Money.h"
#include "AudioManager.h"
#include "Player.h"

Money::Money(int x, int y, int worth, ActorColor color)
	: PlacableActor(x, y, color)
	, m_worth(worth)
	, m_respawnTimer(5)
{
	//
}

ActorType Money::GetType()
{
	return ActorType::Money;
}

int Money::GetWorth() const
{ 
	return m_worth; 
}

void Money::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);
	std::cout << "$";
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}

void Money::HandleCollision(PlacableActor& player)
{
	AudioManager::GetInstance()->PlayMoneySound();
	Remove();
	player.SetPosition(GetPositionX(), GetPositionY());
	dynamic_cast<Player*>(&player)->AddMoney(GetWorth());

	// create thread to respawn
	std::thread RespawnThread(&Money::RespawnTimer, this);
	RespawnThread.detach();
}

void Money::RespawnTimer()
{
	//
	std::this_thread::sleep_for(std::chrono::milliseconds(m_respawnTimer * 1000));
	MakeActive();
}