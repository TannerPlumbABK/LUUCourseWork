#include <iostream>
#include <string>

#include "Player.h"
#include "Key.h"
#include "AudioManager.h"

using namespace std;

constexpr int startingLives = 3;

Player::Player()
	: PlacableActor(0, 0)
	, m_pCurrentKey(nullptr)
	, m_money(0)
	, m_lives(startingLives)
{}

bool Player::HasKey()
{
	return m_pCurrentKey != nullptr;
}

bool Player::HasKey(ActorColor color)
{
	return HasKey() && m_pCurrentKey->GetColor() == color;
}

void Player::PickupKey(Key* key)
{
	m_pCurrentKey = key;
}

void Player::UseKey()
{
	m_pCurrentKey->Remove();
	m_pCurrentKey = nullptr;
}

void Player::DropKey()
{
	if (m_pCurrentKey)
	{
		m_pCurrentKey->Place(m_pPosition->x, m_pPosition->y);
		m_pCurrentKey = nullptr;
		AudioManager::GetInstance()->PlayKeyDropSound();
	}
}

void Player::Draw()
{
	cout << "@";
}

void Player::DisplayPlayerInfo()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	string key = "None ";

	cout << (char)219 << " ";
	SetConsoleTextAttribute(console, (int)ActorColor::Red);
	cout << (char)3 << " " << GetLives() << endl;
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);

	cout << (char)219 << " ";
	SetConsoleTextAttribute(console, (int)ActorColor::Yellow);
	cout << "$" << GetMoney() << endl;
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);


	cout << (char)219 << " ";
	if (HasKey())
	{
		if (m_pCurrentKey->GetColor() == ActorColor::Blue) 
		{
			key = "Blue ";
			SetConsoleTextAttribute(console, (int)ActorColor::Blue);
		}
		else if (m_pCurrentKey->GetColor() == ActorColor::Red) 
		{ 
			key = "Red  ";
			SetConsoleTextAttribute(console, (int)ActorColor::Red);
		}
		else if (m_pCurrentKey->GetColor() == ActorColor::Green) 
		{ 
			key = "Green";
			SetConsoleTextAttribute(console, (int)ActorColor::Green);
		}
	}
	cout << "Key: " << key << endl;
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}