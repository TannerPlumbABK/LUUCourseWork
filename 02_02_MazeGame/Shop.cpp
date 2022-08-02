#include <iostream>
#include <Windows.h>

#include "Shop.h"

using namespace std;

Shop::Shop() : m_shopOdds(0)
{
	//
}

void Shop::LookForShop(Player* player)
{
	srand((unsigned int)time(nullptr));
	int i = (rand() % 100) + 1;
	if (i <= m_shopOdds)
	{
		LoadShop(player);
		m_shopOdds = 0;
	}
	else m_shopOdds += increaseOddsPerLevel;
}

void Shop::LoadShop(Player* player)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	bool doneShopping = false;

	while (!doneShopping)
	{
		system("cls");

		cout << endl << "You found a wandering merchant!" << endl << endl;
		cout << "What would you like to buy?" << endl;

		if (player->GetMoney() >= 50) SetConsoleTextAttribute(console, (int)ActorColor::Green);
		else SetConsoleTextAttribute(console, (int)ActorColor::Red);
		cout << "1. +1 life - 50 coins" << endl;

		if (player->GetMoney() >= 100) SetConsoleTextAttribute(console, (int)ActorColor::Green);
		else SetConsoleTextAttribute(console, (int)ActorColor::Red);
		cout << "2. +3 lives - 100 coins" << endl;

		if (player->GetMoney() >= 150) SetConsoleTextAttribute(console, (int)ActorColor::Green);
		else SetConsoleTextAttribute(console, (int)ActorColor::Red);
		cout << "3. +5 lives - 150 coins" << endl;

		SetConsoleTextAttribute(console, (int)ActorColor::Regular);
		cout << "4. Leave Shop" << endl;

		cout << endl;
		cout << "You have " << player->GetMoney() << (player->GetMoney() > 1 ? " coins." : " coin.") << endl;
		cout << "You have " << player->GetLives() << (player->GetLives() > 1 ? " lives." : " life.") << endl;

		cout << endl << "Choice: ";

		int choice;
		while (true) if (cin >> choice) break;

		cout << endl;

		switch (choice)
		{
		case 1:
			if (player->GetMoney() >= 50)
			{
				player->AddLives(1);
				player->SpendMoney(50);
				cout << "Your purchased 1 life for 50 coins!" << endl;
			}
			else cout << "You don't have enough money for that." << endl;
			break;
		case 2:
			if (player->GetMoney() >= 100)
			{
				player->AddLives(3);
				player->SpendMoney(100);
				cout << "Your purchased 3 lives for 100 coins!" << endl;
			}
			else cout << "You don't have enough money for that." << endl;
			break;
		case 3:
			if (player->GetMoney() >= 150)
			{
				player->AddLives(5);
				player->SpendMoney(150);
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