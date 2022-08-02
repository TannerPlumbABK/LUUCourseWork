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

	m_level.ClearActors();
	m_currentLevelNum = levelNum;
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
			m_shop.LookForShop(&m_player);
			Load(m_currentLevelNum + 1);
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

	DisplayHUD();
}

void Game::DisplayHUD()
{
	cout << endl;
	cout << "            Level " << m_currentLevelNum << endl << endl;
	for (int i = 0; i < 30; i++) cout << (char)219; cout << endl;
	cout << (char)219 << " WASD or Arrow Keys to move " << (char)219 << endl;
	cout << (char)219 << " Z to drop a key            " << (char)219 << endl;
	cout << (char)219 << " R to restart level         " << (char)219 << endl;
	for (int i = 0; i < 30; i++) cout << (char)219; cout << endl;
	cout << endl;
	m_player.DisplayPlayerInfo();
}