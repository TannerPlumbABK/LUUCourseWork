#include <iostream>
#include <string>

#define NOMINMAX
#include "Game.h"
#include "AudioManager.h"

using namespace std;

void DrawFancyLogo();

int main()
{
	Game myGame;

	DrawFancyLogo();
	cout << "\tWhat would you like to do?" << endl;
	cout << "\t1 - Play" << endl;
	cout << "\t2 - Quit" << endl;
	cout << "\t------------------" << endl;
	cout << "\tChoice: ";

	int choice;
	while (true)
	{
		if (cin >> choice && choice > 0 && choice < 3) break;
		else
		{
			cout << "\tPick a valid option: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	if (choice == 2)
	{
		cout << "\n\tThanks for playing!" << endl;
		return 0;
	}

	if (myGame.Load(1))
	{
		while (!myGame.IsGameOver())
		{
			myGame.Run();
		}

		if (myGame.DidUserQuit())
		{
			cout << "Thanks for playing!" << endl;
		}
		else if (myGame.GetPlayerLives() <= 0)
		{
			cout << "You lose!" << endl;
			AudioManager::GetInstance()->PlayLoseSound();
		}
		else
		{
			cout << "You won!" << endl;
			AudioManager::GetInstance()->PlayWinSound();
		}

		cout << endl << "Would you like to play again?" << endl;
		cout << "1 - Yes" << endl;
		cout << "2 - No" << endl;
		cout << "Choice: ";

		int input;
		while (true)
		{
			if (cin >> input && input > 0 && input < 3) break;
			else
			{
				cout << "Pick a valid choice: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}

		if (input == 1)
		{
			system("cls");
			main();
		}
		else if (input == 2)
		{
			cout << "Thanks for playing!" << endl;
			return 0;
		}
	}
	else
	{
		cout << "Game did not load. Teminating now." << endl;
	}

	AudioManager::DestroyInstance();

	return 0;
}

void DrawFancyLogo()
{
	cout << endl << endl;

	cout << " ||          ||   ||||||   |||||||||| ||||||||||     |||||||| ||    || ||      || ||      || |||||||||| ||||||||" << endl;
	cout << " ||||      |||| ||      ||         || ||             ||    || ||    || ||||    || ||||    || ||         ||    ||" << endl;
	cout << " ||  ||  ||  || ||      ||       ||   ||             ||   ||  ||    || || ||   || || ||   || ||         ||   || " << endl;
	cout << " ||    ||    || ||      ||     ||     ||||||         ||||||   ||    || ||  ||  || ||  ||  || ||||||     ||||||  " << endl;
	cout << " ||          || ||||||||||   ||       ||             ||  ||   ||    || ||   || || ||   || || ||         ||  ||  " << endl;
	cout << " ||          || ||      || ||         ||             ||   ||  ||    || ||    |||| ||    |||| ||         ||   || " << endl;
	cout << " ||          || ||      || |||||||||| ||||||||||     ||    || |||||||| ||      || ||      || |||||||||| ||    ||" << endl;

	cout << endl << endl;
}