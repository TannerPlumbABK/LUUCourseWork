#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <random>

using namespace std;

void ProduceHoney();
void TakeHoney();
void DisplayInfo();
int GetRandomNum(int min, int max);

static bool gatheringHoney = true;
static bool honeyInContainer = false;
static int containersOfHoney = 0;
static int beesWithHoney = 0;

int main()
{
	thread HoneyThread1(ProduceHoney);
	thread HoneyThread2(ProduceHoney);
	thread HoneyThread3(ProduceHoney);
	thread HoneyThread4(ProduceHoney);
	thread FarmerThread(TakeHoney);
	thread DisplayThread(DisplayInfo);

	// use _getch() so we can exit on any keyboard input
	// this basically just acts as a system("pause")
	char input = _getch();
	gatheringHoney = false;

	// detach everything and end the program on input
	HoneyThread1.detach();
	HoneyThread2.detach();
	HoneyThread3.detach();
	HoneyThread4.detach();
	FarmerThread.detach();
	DisplayThread.detach();

	return 0;
}

int GetRandomNum(int min, int max)
{
	thread_local mt19937 generator(random_device{}());
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

void ProduceHoney()
{
	while (gatheringHoney)
	{
		int seconds = GetRandomNum(1, 15);

		// "gather" honey for random time from 5-15 seconds
		this_thread::sleep_for(chrono::milliseconds(seconds * 1000));
		
		// increment beesWithHoney 
		beesWithHoney += 1;

		// if honey is present, wait 1-5 seconds and try again
		while (honeyInContainer)
		{
			this_thread::sleep_for(chrono::milliseconds(rand() % 5 + 1 * 1000));
		}

		// put honey in the container
		honeyInContainer = true;

		// decrement beesWithHoney
		beesWithHoney -= 1;
	}
}

void TakeHoney()
{
	while (gatheringHoney)
	{
		if (honeyInContainer)
		{
			// wait 3 seconds so bees aren't near the container
			this_thread::sleep_for(chrono::milliseconds(3 * 1000));
			containersOfHoney += 1;
			honeyInContainer = false;
		}
	}
}

void DisplayInfo()
{
	while (gatheringHoney)
	{
		this_thread::sleep_for(chrono::milliseconds(1000));
		system("cls");
		cout << endl << "\tPress any key to quit." << endl << endl;

		cout << "Honey Gathered: " << containersOfHoney << endl;
		cout << "Container contains honey: " << (honeyInContainer ? "Yes" : "No") << endl;
		cout << "Num Bees currently holding honey: " << beesWithHoney << endl;
	}
}