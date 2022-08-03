#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

bool didQuit = false;
bool shouldDecrementLife = false;
mutex Mutex;

struct Character
{
	float position = 0.0f;
	atomic<int> score = 0;
	int lives = 1;

	void DisplayStats()
	{
		cout << "Lives: " << lives << endl;
	}
};

void UpdateCharacter();
void ProcessInput();

Character player;

int main()
{
	thread InputHandler(ProcessInput);
	thread CharacterUpdate1(UpdateCharacter);
	thread CharacterUpdate2(UpdateCharacter);

	InputHandler.join();
	CharacterUpdate1.join();
	CharacterUpdate2.join();

	return 0;
}

void UpdateCharacter()
{
	while (!didQuit)
	{
		if (shouldDecrementLife)
		{
			//lock_guard<mutex> Guard(Mutex);
			if (player.lives > 0)
			{
				//this_thread::sleep_for(chrono::milliseconds(500));
				//this_thread::yield();
				player.lives -= 1;
			}

			shouldDecrementLife = false;
		}
	}
}

void ProcessInput()
{
	while (!didQuit)
	{
		cout << "a - decrement player life" << endl;
		cout << "d - display player lives" << endl;
		cout << "q - quit" << endl;
		cout << "Choice: ";
		char input;
		cin >> input;
		switch (input)
		{
		case 'a':
		case 'A':
			shouldDecrementLife = true;
			break;
		case 'd':
		case 'D':
			player.DisplayStats();
			break;
		case 'q':
		case 'Q':
			didQuit = true;
			break;
		default:
			break;
		}
		didQuit = (input == 'q' || input == 'Q');
	}
}