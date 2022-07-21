#include "Game.h"

using namespace std;

constexpr int openDoorColor = 10;
constexpr int closedDoorColor = 12;
constexpr int regularColor = 7;

Game::Game()
	: m_isGameOver(false)
{

}

Game::~Game()
{

}

bool Game::Load()
{
	return m_level.Load("Level1.txt", m_player.GetPositionXPointer(), m_player.GetPositionYPointer());
}

void Game::Run() 
{
	Draw();

	m_isGameOver = Update();

	if (IsGameOver())
	{
		//
	}
}

bool Game::Update()
{
	char input = (char)_getch();

	int newPlayerX = m_player.GetPositionX();
	int newPlayerY = m_player.GetPositionY();

	switch (input)
	{
	case 'W':
	case 'w':
		newPlayerY--;
		break;
	case 'S':
	case 's':
		newPlayerY++;
		break;
	case 'A':
	case 'a':
		newPlayerX--;
		break;
	case 'D':
	case 'd':
		newPlayerX++;
		break;
	default:
		break;
	}

	if (m_level.IsSpace(newPlayerX, newPlayerY))
	{
		m_player.SetPosition(newPlayerX, newPlayerY);
	}
	else if (m_level.IsKey(newPlayerX, newPlayerY))
	{
		m_player.SetPosition(newPlayerX, newPlayerY);
		m_player.PickupKey();
		m_level.ClearSpace(newPlayerX, newPlayerY);

		//PlaySoundPickupKey();
	}
	else if (m_level.IsDoor(newPlayerX, newPlayerY))
	{
		if (m_player.HasKey())
		{
			m_player.SetPosition(newPlayerX, newPlayerY);
			m_player.UseKey();
			m_level.ClearSpace(newPlayerX, newPlayerY);

			//PlaySoundDoorOpened();
		}
		else
		{
			//PlaySoundDoorClosed();
		}
	}
	else if (m_level.IsGoal(newPlayerX, newPlayerY))
	{
		m_player.SetPosition(newPlayerX, newPlayerY);
		m_level.ClearSpace(newPlayerX, newPlayerY);
		return true;
	}

	return false;
}

void Game::Draw()
{
	system("cls");

	for (int y = 0; y < m_level.GetHeight(); y++)
	{
		for (int x = 0; x < m_level.GetWidth(); x++)
		{
			if (m_player.GetPositionX() == x && m_player.GetPositionY() == y)
			{
				m_player.Draw();
			}
			else
			{
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

				if (m_level.IsDoor(x, y))
				{
					if (m_player.HasKey())
					{
						SetConsoleTextAttribute(console, openDoorColor);
					}
					else
					{
						SetConsoleTextAttribute(console, closedDoorColor);
					}
				}
				else
				{
					SetConsoleTextAttribute(console, regularColor);
				}

				m_level.Draw(x, y);
			}
		}

		cout << endl;
	}
}