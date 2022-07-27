#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <assert.h>

#include "Game.h"
#include "Key.h"
#include "Door.h"
#include "Money.h"
#include "Goal.h"
#include "Enemy.h"
#include "AudioManager.h"
#include "PortalEntrance.h"
#include "PortalExit.h"

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
{
	//
}

Game::~Game()
{
	//
}

bool Game::Load(string levelName)
{
	return m_level.Load(levelName, m_player.GetPositionXPointer(), m_player.GetPositionYPointer());
}

void Game::Run() 
{
	Draw();

	m_isGameOver = Update();

	if (m_isGameOver)
	{
		Draw();
	}
}

bool Game::Update()
{
	char input = (char)_getch();
	int arrowInput = 0;
	int newPlayerX = m_player.GetPositionX();
	int newPlayerY = m_player.GetPositionY();

	if (input == arrowInput)
	{
		arrowInput = _getch();
	}

	if ((input == arrowInput && arrowInput == leftArrow) ||
		(char)input == 'A' || (char)input == 'a')
	{
		newPlayerX -= 1;
	}
	else if ((input == arrowInput && arrowInput == rightArrow) ||
		(char)input == 'D' || (char)input == 'd')
	{
		newPlayerX += 1;
	}
	else if ((input == arrowInput && arrowInput == upArrow) ||
		(char)input == 'W' || (char)input == 'w')
	{
		newPlayerY -= 1;
	}
	else if ((input == arrowInput && arrowInput == downArrow) ||
		(char)input == 'S' || (char)input == 's')
	{
		newPlayerY += 1;
	}
	else if (input == escapeKey)
	{
		m_userQuit = true;
		return true;
	}
	else if ((char)input == 'Z' || (char)input == 'z')
	{
		m_player.DropKey();
	}

	// if position didn't change
	if (newPlayerX == m_player.GetPositionX() && newPlayerY == m_player.GetPositionY())
	{
		return false;
	}
	else
	{
		return HandleCollision(newPlayerX, newPlayerY);
	}
}

bool Game::HandleCollision(int newPlayerX, int newPlayerY)
{
	bool isGameDone = false;
	PlacableActor* collidedActor = m_level.UpdateActors(newPlayerX, newPlayerY);

	if (collidedActor != nullptr && collidedActor->IsActive())
	{
		switch (collidedActor->GetType())
		{
		case ActorType::Enemy:
		{
			Enemy* collidedEnemy = dynamic_cast<Enemy*>(collidedActor);
			assert(collidedEnemy);
			AudioManager::GetInstance()->PlayLoseLivesSound();
			collidedEnemy->Remove();
			m_player.SetPosition(newPlayerX, newPlayerY);
			m_player.DecrementLives();

			if (m_player.GetLives() < 0)
			{
				isGameDone = true;
			}
			break;
		}
		case ActorType::Money:
		{
			Money* collidedMoney = dynamic_cast<Money*>(collidedActor);
			assert(collidedMoney);
			AudioManager::GetInstance()->PlayMoneySound();
			collidedMoney->Remove();
			m_player.AddMoney(collidedMoney->GetWorth());
			m_player.SetPosition(newPlayerX, newPlayerY);
			break;
		}
		case ActorType::Key:
		{
			Key* collidedKey = dynamic_cast<Key*>(collidedActor);
			assert(collidedKey);
			if (!m_player.HasKey())
			{
				m_player.PickupKey(collidedKey);
				collidedKey->Remove();
				m_player.SetPosition(newPlayerX, newPlayerY);
				AudioManager::GetInstance()->PlayKeyPickupSound();
			}
			break;
		}
		case ActorType::Door:
		{
			Door* collidedDoor = dynamic_cast<Door*>(collidedActor);
			assert(collidedDoor);
			if (!collidedDoor->IsOpen())
			{
				if (m_player.HasKey(collidedDoor->GetColor()))
				{
					collidedDoor->Open();
					collidedDoor->Remove();
					m_player.UseKey();
					m_player.SetPosition(newPlayerX, newPlayerY);
					AudioManager::GetInstance()->PlayDoorOpenSound();
				}
				else AudioManager::GetInstance()->PlayDoorClosedSound();
			}
			else
			{
				m_player.SetPosition(newPlayerX, newPlayerY);
			}
			break;
		}
		case ActorType::Goal:
		{
			Goal* collidedGoal = dynamic_cast<Goal*>(collidedActor);
			assert(collidedGoal);
			collidedGoal->Remove();
			m_player.SetPosition(newPlayerX, newPlayerY);
			isGameDone = true;
			break;
		}
		case ActorType::PortalEntrance:
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
			break;
		}
		default:
			break;
		}
	}
	else if (m_level.IsSpace(newPlayerX, newPlayerY))
	{
		m_player.SetPosition(newPlayerX, newPlayerY);
	}
	else if (m_level.IsWall(newPlayerX, newPlayerY))
	{
		// wall collision, do nothing
	}

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
}