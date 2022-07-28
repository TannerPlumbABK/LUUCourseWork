// Functions with more comments in them are the ones that I didn't grasp
// as easily. The comments should help me navigate what's happening better.

#include <iostream>
#include <chrono>
#include <stdlib.h>
#define NOMINMAX
#include <Windows.h>

#define ARRAY_SIZE 100

using namespace std;

// CinFunctions
void CinSorts();
void CinSearches();
void ClearCin();

// Helper functions
void FillArray(int arrayToFill[], int arraySize);
void DisplayArray(int arr[], int indexToHighlight = -1);
int QuickSortPartition(int arr[], int low, int high);

// Sorting functions
void BubbleSort(int arr[], int arraySize);
void SelectionSort(int arr[], int arraySize);
void InsertionSort(int arr[], int arraySize);
void QuickSort(int arr[], int low, int high);

// Searching functions
int LinearSearch(int arr[], int valueToFind);
int BinarySearch(int arr[], int low, int high, int searchKey);

// Tower of Hanoi
void SolveTowerOfHanoi(int numDiscs, int stackOne, int stackTwo, int stackThree, int& numMoves);
void TowerOfHanoi(int numDisks);

/***************************************************************
***************************** MAIN *****************************
****************************************************************/
int main()
{
	bool done = false;

	while (!done)
	{
		cout << "Please select an option." << endl;
		cout << "0. Quit" << endl;
		cout << "1. Sorting Algorithms" << endl;
		cout << "2. Searching Algorithms" << endl;
		cout << "3. Tower of Hanoi" << endl;
		cout << "Choice: ";

		int choice;
		while (true)
		{
			if (cin >> choice) break;
			else
			{
				ClearCin();
				choice = -1;
				break;
			}
		}

		switch (choice)
		{
		case 0:
			done = true;
			break;
		case 1:
			CinSorts();
			break;
		case 2:
			CinSearches();
			break;
		case 3:
			int numDisks;
			cout << "How many discs are there?" << endl;
			cout << "Discs: ";
			while (true)
			{
				if (cin >> numDisks) break;
				else
				{
					cout << "Enter a valid number of discs: ";
					ClearCin();
				}
			}
			TowerOfHanoi(numDisks);
		default:
			break;
		}

		system("cls");
	}
}

/***************************************************************
***************************** CIN ******************************
****************************************************************/
void ClearCin()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void CinSorts()
{
	bool done = false;

	system("cls");

	while (!done)
	{
		srand(time(nullptr));
		int Dataset[ARRAY_SIZE];
		FillArray(Dataset, ARRAY_SIZE);

		cout << "Please select an option: " << endl;
		cout << "0. Quit" << endl;
		cout << "1. Bubble Sort" << endl;
		cout << "2. Selection Sort" << endl;
		cout << "3. Insertion Sort" << endl;
		cout << "4. Quick Sort" << endl;
		cout << "Choice: ";

		int choice;
		while (true)
		{
			if (cin >> choice) break;
			else
			{
				ClearCin();
				choice = -1;
				break;
			}
		}

		cout << endl;

		switch (choice)
		{
		case 0:
			done = true;
			system("cls");
			break;
		case 1:
			cout << "Bubble Sort" << endl << endl;
			cout << "BEFORE on top, AFTER on bottom" << endl << endl;
			DisplayArray(Dataset);
			BubbleSort(Dataset, ARRAY_SIZE);
			DisplayArray(Dataset);
			system("pause");
			break;
		case 2:
			cout << "Selection Sort" << endl << endl;
			cout << "BEFORE on top, AFTER on bottom" << endl << endl;
			DisplayArray(Dataset);
			SelectionSort(Dataset, ARRAY_SIZE);
			DisplayArray(Dataset);
			system("pause");
			break;
		case 3:
			cout << "Insertion Sort" << endl << endl;
			cout << "BEFORE on top, AFTER on bottom" << endl << endl;
			DisplayArray(Dataset);
			InsertionSort(Dataset, ARRAY_SIZE);
			DisplayArray(Dataset);
			system("pause");
			break;
		case 4:
			cout << "Quick Sort" << endl << endl;
			cout << "BEFORE on top, AFTER on bottom" << endl << endl;
			DisplayArray(Dataset);
			QuickSort(Dataset, 0, ARRAY_SIZE - 1);
			DisplayArray(Dataset);
			system("pause");
			break;
		default:
			break;
		}

		system("cls");
	}
}

void CinSearches()
{
	bool done = false;

	system("cls");

	while (!done)
	{
		srand(time(nullptr));
		int Dataset[ARRAY_SIZE];
		FillArray(Dataset, ARRAY_SIZE);
		BubbleSort(Dataset, ARRAY_SIZE);

		cout << "Please select an option: " << endl;
		cout << "0. Quit" << endl;
		cout << "1. Linear Search" << endl;
		cout << "2. Binary Search" << endl;
		cout << "Choice: ";

		int choice;
		while (true)
		{
			if (cin >> choice) break;
			else
			{
				ClearCin();
				choice = -1;
				break;
			}
		}

		cout << endl;

		switch (choice)
		{
		case 0:
			done = true;
			break;
		case 1:
		{
			// Linear Search
			cout << "An array with 100 random numbers between 1-100 has been created." << endl;
			cout << "What number would you like to check the array for?" << endl;
			cout << "Number: ";
			int search;
			while (true)
			{
				if (cin >> search) break;
				else
				{
					ClearCin();
					cout << "Input a valid number: ";
				}
			}
			cout << endl;

			int index = LinearSearch(Dataset, search);

			if (index == -1) cout << search << " is not in the array." << endl << endl;
			else cout << search << " was found at index " << index << "." << endl << endl;

			cout << "Full array below: " << endl;
			DisplayArray(Dataset, index);

			system("pause");
			break;
		}
		case 2: {
			// Binary Search
			cout << "An array with 100 random numbers between 1-100 has been created." << endl;
			cout << "What number would you like to check the array for?" << endl;
			cout << "Number: ";
			int search;
			while (true)
			{
				if (cin >> search) break;
				else
				{
					ClearCin();
					cout << "Input a valid number: ";
				}
			}
			cout << endl;

			int index = BinarySearch(Dataset, 0, ARRAY_SIZE, search);

			if (index == -1) cout << search << " is not in the array." << endl << endl;
			else cout << search << " was found at index " << index << "." << endl << endl;

			cout << "Full array below: " << endl;
			DisplayArray(Dataset, index);

			system("pause");
			break; }
		default:
			break;
		}

		system("cls");
	}
}

/***************************************************************
*************************** HELPERS ****************************
****************************************************************/
void FillArray(int arrayToFill[], int arraySize)
{
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		arrayToFill[i] = rand() % ARRAY_SIZE + 1;
	}
}

void DisplayArray(int arr[], int indexToHighlight)
{
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

		if (indexToHighlight == i)
		{
			SetConsoleTextAttribute(console, 10);
		}

		cout << arr[i] << " ";
		SetConsoleTextAttribute(console, 7);
	}
	cout << endl << endl;
}

int QuickSortPartition(int arr[], int low, int high)
{
	// start with the end of the array
	int pivot = arr[high];

	// start compare index at beginning of array
	int lowIndex = (low - 1);

	// compare all elements to the pivot value
	for (int i = low; i < high; i++) {
		if (arr[i] <= pivot) {
			// if we find a value that's less than the pivot value, we should swap it and increment the lowIndex
			lowIndex++;
			swap(arr[lowIndex], arr[i]);
		}
	}

	// now that we've found the highest value, we should swap it with pivot
	swap(arr[lowIndex + 1], arr[high]);

	return (lowIndex + 1);
}

/***************************************************************
**************************** SORTS *****************************
****************************************************************/
void BubbleSort(int arr[], int arraySize)
{
	for (int pass = 0; pass < arraySize; ++pass)
	{
		for (int i = 0; i < arraySize - 1; ++i)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
			}
		}
	}
}

void SelectionSort(int arr[], int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		int smallestNum = arr[i];

		for (int secondIndex = i; secondIndex < arraySize; secondIndex++)
		{
			if (arr[secondIndex] < smallestNum)
			{
				arr[i] = arr[secondIndex];
				arr[secondIndex] = smallestNum;
				smallestNum = arr[i];
			}
		}
	}
}

void InsertionSort(int arr[], int arraySize)
{
	for (int i = 1; i < arraySize; i++)
	{
		int temp = arr[i];
		int prevIndex = i - 1;

		while (prevIndex >= 0 && temp <= arr[prevIndex])
		{
			arr[prevIndex + 1] = arr[prevIndex];
			prevIndex = prevIndex - 1;
		}

		arr[prevIndex + 1] = temp;
	}
}

void QuickSort(int arr[], int low, int high)
{
	if (low < high) {
		// get pivot
		int pivot = QuickSortPartition(arr, low, high);

		// repeat before pivot
		QuickSort(arr, low, pivot - 1);

		// repeat after pivot
		QuickSort(arr, pivot + 1, high);
	}
}

/***************************************************************
*************************** SEARCHES ***************************
****************************************************************/
int LinearSearch(int arr[], int valueToFind)
{
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		if (arr[i] == valueToFind) return i;
	}

	return -1;
}

int BinarySearch(int arr[], int low, int high, int searchKey)
{
	while (low <= high)
	{
		int middle = (low + high) / 2;

		if (searchKey == arr[middle]) return middle;
		else if (searchKey < arr[middle]) high = middle - 1;
		else low = middle + 1;
	}

	return -1;
}

/***************************************************************
************************ TOWER OF HANOI ************************
****************************************************************/
/* ILLUSTRATION OF WHAT'S HAPPENING
* TODO
* 
*/
void SolveTowerOfHanoi(int numDiscs, int fromStack, int toStack, int extraStack, int &numMoves)
{
	if (numDiscs == 0) return;
	SolveTowerOfHanoi(numDiscs - 1, fromStack, extraStack, toStack, numMoves);
	cout << "Move disc " << numDiscs << " from stack " << fromStack << " to " << toStack << endl;
	SolveTowerOfHanoi(numDiscs - 1, extraStack, toStack, fromStack, numMoves);
	numMoves += 1;
}

void TowerOfHanoi(int numDiscs)
{
	int numMoves = 0;
	SolveTowerOfHanoi(numDiscs, 1, 3, 2, numMoves);
	cout << "Number of moves made: " << numMoves << endl;
	system("pause");
}