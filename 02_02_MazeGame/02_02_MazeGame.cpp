#include <iostream>

#include "Game.h"

using namespace std;

int main()
{
	Game myGame;
	if (myGame.Load())
	{
		while (!myGame.IsGameOver())
		{
			myGame.Run();
		}

		cout << "You won!" << endl;
		// Play win sound
	}
	else
	{
		cout << "Game did not load. Teminating now." << endl;
	}
}

//void PlaySoundDoorClosed()
//{
//	Beep(500, 35);
//	Beep(500, 35);
//}
//
//void PlaySoundDoorOpened()
//{
//	Beep(1397, 100);
//}
//
//void PlaySoundPickupKey()
//{
//	Beep(1568, 100);
//}
//
//void PlaySoundWin()
//{
//	Beep(1568, 100);
//	Beep(1568, 100);
//	Beep(1568, 100);
//	Beep(1245, 500);
//	Beep(1397, 100);
//	Beep(1397, 100);
//	Beep(1397, 100);
//	Beep(1175, 500);
//}