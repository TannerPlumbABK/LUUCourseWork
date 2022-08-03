#include <iostream>
#include <string>

#define NOMINMAX
#include "Game.h"
#include "AudioManager.h"

using namespace std;

constexpr char line = (char)196;

void DrawFancyLogo();
void DisplayMenu();
int GetChoice();
void LoadGame(Game& myGame);
void AskPlayAgain();

int main()
{
	system("cls");
	Game myGame;

	DrawFancyLogo();
	DisplayMenu();
	int option = GetChoice();

	switch (option)
	{
	case 1:
		// PLAY
		system("cls");
		LoadGame(myGame);
		break;
	case 2:
		// QUIT
		cout << "\n\tThanks for playing!" << endl;
		return 0;
		break;
	default:
		break;
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

void DisplayMenu()
{
	cout << "\tWhat would you like to do?" << endl;
	cout << "\t1 - Play" << endl;
	cout << "\t2 - Quit" << endl;
	cout << "\t";
	for (int i = 0; i < 25; i++) cout << line;
	cout << endl;
}

int GetChoice()
{
	int choice;

	cout << "\tChoice: ";
	while (true)
	{
		if (cin >> choice  && choice > 0 && choice < 3) break;
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("cls");
			DrawFancyLogo();
			DisplayMenu();
			cout << "\tChoice: ";
		}
	}

	return choice;
}

void LoadGame(Game& myGame)
{
	if (myGame.Load(1))
	{
		while (!myGame.IsGameOver()) myGame.Run();

		system("cls");
		if (myGame.DidUserQuit()) cout << "Thanks for playing!" << endl;
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

		AskPlayAgain();
	}
	else cout << "Game did not load. Teminating now." << endl;
}

void AskPlayAgain()
{
	cout << endl << "Would you like to play again?" << endl;
	cout << "1 - Yes" << endl;
	cout << "2 - No" << endl;
	for (int i = 0; i < 25; i++) cout << line;
	cout << "\nChoice: ";

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

	if (input == 1) main();
	else if (input == 2) cout << "Thanks for playing!" << endl;
}