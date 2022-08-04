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
void GetInput();

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

	GetInput();

	// detach everything and end the program on input
	HoneyThread1.detach();
	HoneyThread2.detach();
	HoneyThread3.detach();
	HoneyThread4.detach();
	FarmerThread.detach();
	DisplayThread.detach();

	return 0;
}

void GetInput()
{
	char input = _getch();
	gatheringHoney = false;
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
		int timeToGather = GetRandomNum(5, 15);

		// "gather" honey for random time from 5-15 seconds
		this_thread::sleep_for(chrono::seconds(timeToGather));
		
		// increment beesWithHoney 
		beesWithHoney += 1;

		// if honey is present, wait 1-5 seconds and try again
		while (honeyInContainer)
		{
			this_thread::sleep_for(chrono::seconds(GetRandomNum(1, 5)));
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
			this_thread::sleep_for(chrono::seconds(3));
			containersOfHoney += 1;
			honeyInContainer = false;
		}
	}
}

void DisplayInfo()
{
	while (gatheringHoney)
	{
		this_thread::sleep_for(chrono::seconds(1));
		system("cls");
		cout << endl;
		cout << "                          Press any key to quit." << endl << endl;

		cout << "                     Honey Gathered: " << containersOfHoney << endl;
		cout << "           Container contains honey: " << (honeyInContainer ? "Yes" : "No") << endl;
		cout << "   Num Bees currently holding honey: " << beesWithHoney << endl;
		cout << " Num Bees currently gathering honey: " << (4 - beesWithHoney) << endl;
	}
}