#include <iostream>
#include <string>

#define NOMINMAX
#include "Game.h"
#include "AudioManager.h"

using namespace std;

int main()
{
	Game myGame;
	string levelToLoad = "Level";

	cout << "What level would you like to play?" << endl;
	cout << "1 - Level 1" << endl;
	cout << "2 - Level 2" << endl;
	cout << "Choice: ";

	int levelInput;
	while (true)
	{
		if (cin >> levelInput && levelInput > 0 && levelInput < 3) break;
		else
		{
			cout << "Pick a valid level: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	levelToLoad.append(to_string(levelInput));
	levelToLoad.append(".txt");

	if (myGame.Load(levelToLoad))
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