#include <iostream>
#include <conio.h>
#define NOMINMAX
#include <Windows.h>
#include <assert.h>
#include <string>
#include <chrono>
#include <stdlib.h>
#include <map>

#include "Game.h"
#include "Key.h"
#include "Door.h"
#include "Money.h"
#include "Goal.h"
#include "Enemy.h"
#include "AudioManager.h"
#include "PortalEntrance.h"
#include "PortalExit.h"
#include "Life.h"

using namespace std;

constexpr int arrowInput = 224;
constexpr int leftArrow = 75;
constexpr int rightArrow = 77;
constexpr int upArrow = 72;
constexpr int downArrow = 80;
constexpr int escapeKey = 27;

Game::Game()
	: m_isGameOver(false)
	, m_userQuit(false)
	, m_currentLevelNum(1)
	, m_shopOdds(startingShopOdds)
{
	//
}

bool Game::Load(int levelNum)
{
	string levelName = "Level";
	levelName.append(to_string(levelNum));
	levelName.append(".txt");

	return m_level.Load(levelName, m_player.GetPositionXPointer(), m_player.GetPositionYPointer());
}

void Game::Run() 
{
	Draw();
	m_isGameOver = Update();
	if (m_isGameOver) Draw();
}

bool Game::IsGameOver()
{ 
	return m_isGameOver; 
}

bool Game::DidUserQuit()
{ 
	return m_userQuit; 
}

int Game::GetPlayerLives()
{ 
	return m_player.GetLives();
}

bool Game::Update()
{
	return ProcessInput();
}

bool Game::ProcessInput()
{
	char input = _getch();

	int newPlayerX = m_player.GetPositionX();
	int newPlayerY = m_player.GetPositionY();

	if (input == 0 || input == 0xE0) input = _getch();

	if (input == leftArrow || (char)input == 'A' || (char)input == 'a') newPlayerX -= 1;
	else if (input == rightArrow || (char)input == 'D' || (char)input == 'd') newPlayerX += 1;
	else if (input == upArrow || (char)input == 'W' || (char)input == 'w') newPlayerY -= 1;
	else if (input == downArrow || (char)input == 'S' || (char)input == 's') newPlayerY += 1;
	else if ((char)input == 'r' || (char)input == 'R')
	{
		m_player.DecrementLives();

		if (m_player.GetLives() <= 0) return true;

		m_level.ClearActors();
		Load(m_currentLevelNum);
		return false;
	}
	else if (input == escapeKey)
	{
		m_userQuit = true;
		return true;
	}
	else if ((char)input == 'Z' || (char)input == 'z') m_player.DropKey();

	// if position didn't change
	if (newPlayerX == m_player.GetPositionX() && newPlayerY == m_player.GetPositionY()) return false;
	else return HandleCollision(newPlayerX, newPlayerY);
}

void CollideWithActor(PlacableActor* actor)
{
	//
}

bool Game::HandleCollision(int newPlayerX, int newPlayerY)
{
	bool isGameDone = false;
	PlacableActor* collidedActor = m_level.UpdateActors(newPlayerX, newPlayerY);

	if (collidedActor != nullptr)
	{
		collidedActor->HandleCollision(m_player);

		if (m_player.GetLives() <= 0
			|| m_currentLevelNum >= maxLevel) 
				isGameDone = true;

		if (collidedActor->GetType() == ActorType::Goal)
		{
			m_currentLevelNum += 1;

			srand((unsigned int)time(nullptr));
			int i = (rand() % 100) + 1;
			if (i <= m_shopOdds)
			{
				// load shop
				LoadShop();

				m_shopOdds = 0;
			}
			else m_shopOdds += increasingOddsPerLevel;

			m_level.ClearActors();
			Load(m_currentLevelNum);
		}
		else if (collidedActor->GetType() == ActorType::PortalEntrance)
		{
			PortalEntrance* collidedPortal = dynamic_cast<PortalEntrance*>(collidedActor);
			assert(collidedPortal);
			for (int i = 0; i < (int)m_level.GetActors().size(); i++)
			{
				PlacableActor* actor = m_level.GetActors()[i];
				if (actor->GetType() == ActorType::PortalExit)
				{
					m_player.SetPosition(actor->GetPositionX(), actor->GetPositionY());
					break;
				}
			}
		}
	}
	else if (m_level.IsSpace(newPlayerX, newPlayerY)) m_player.SetPosition(newPlayerX, newPlayerY);
	else if (m_level.IsWall(newPlayerX, newPlayerY)) { /* do nothing */ }

	return isGameDone;
}

void Game::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	m_level.Draw();

	COORD actorCursorPosition;
	actorCursorPosition.X = m_player.GetPositionX();
	actorCursorPosition.Y = m_player.GetPositionY();
	SetConsoleCursorPosition(console, actorCursorPosition);
	m_player.Draw();

	COORD currentCursorPosition;
	currentCursorPosition.X = 0;
	currentCursorPosition.Y = m_level.GetHeight();
	SetConsoleCursorPosition(console, currentCursorPosition);

	// display some extra info
	cout << endl;
	cout << "            Level " << m_currentLevelNum << endl << endl;
	DisplayDirections();
	m_player.DisplayPlayerInfo();
}

void Game::DisplayDirections()
{
	for (int i = 0; i < 30; i++) cout << (char)219; cout << endl;
	cout << (char)219 << " WASD or Arrow Keys to move " << (char)219 << endl;
	cout << (char)219 << " Z to drop a key            " << (char)219 << endl;
	cout << (char)219 << " R to restart level         " << (char)219 << endl;
	for (int i = 0; i < 30; i++) cout << (char)219; cout << endl;
	cout << endl;
}

void Game::LoadShop()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	bool doneShopping = false;

	while (!doneShopping)
	{
		system("cls");

		cout << endl << "You found a wandering merchant!" << endl << endl;
		cout << "What would you like to buy?" << endl;

		if (m_player.GetMoney() >= 50) SetConsoleTextAttribute(console, (int)ActorColor::Green);
		else SetConsoleTextAttribute(console, (int)ActorColor::Red);
		cout << "1. +1 life - 50 coins" << endl;

		if (m_player.GetMoney() >= 100) SetConsoleTextAttribute(console, (int)ActorColor::Green);
		else SetConsoleTextAttribute(console, (int)ActorColor::Red);
		cout << "2. +3 lives - 100 coins" << endl;

		if (m_player.GetMoney() >= 150) SetConsoleTextAttribute(console, (int)ActorColor::Green);
		else SetConsoleTextAttribute(console, (int)ActorColor::Red);
		cout << "3. +5 lives - 150 coins" << endl;

		SetConsoleTextAttribute(console, (int)ActorColor::Regular);
		cout << "4. Leave Shop" << endl;

		cout << endl;
		cout << "You have " << m_player.GetMoney() << (m_player.GetMoney() > 1 ? " coins." : " coin.") << endl;
		cout << "You have " << m_player.GetLives() << (m_player.GetLives() > 1 ? " lives." : " life.") << endl;

		cout << endl << "Choice: ";

		int choice;
		while (true) if (cin >> choice) break;

		cout << endl;

		switch (choice)
		{
		case 1:
			if (m_player.GetMoney() >= 50)
			{
				m_player.AddLives(1);
				m_player.SpendMoney(50);
				cout << "Your purchased 1 life for 50 coins!" << endl;
			}
			else cout << "You don't have enough money for that." << endl; 
			break;
		case 2:
			if (m_player.GetMoney() >= 100)
			{
				m_player.AddLives(3);
				m_player.SpendMoney(100);
				cout << "Your purchased 3 lives for 100 coins!" << endl;
			}
			else cout << "You don't have enough money for that." << endl; 
			break;
		case 3:
			if (m_player.GetMoney() >= 150)
			{
				m_player.AddLives(5);
				m_player.SpendMoney(150);
				cout << "Your purchased 5 lives for 150 coins!" << endl;
			}
			else cout << "You don't have enough money for that." << endl;
			break;
		case 4:
		default:
			doneShopping = true;
			break;
		}

		cout << endl;

		if (!doneShopping) system("pause");

	}

	cout << "Thanks for visiting the shop!" << endl << endl;
	system("pause");
}