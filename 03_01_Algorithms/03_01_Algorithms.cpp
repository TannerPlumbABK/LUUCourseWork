// Functions with more comments in them are the ones that I didn't grasp
// as easily. The comments should help me navigate what's happening better.

/*
Big O Notation
O(1) = takes exactly the same amount of time to run no matter how big the array is
O(n) = increases in time required linearly based on how big the array is
O(log n) = increases logarithmically in time required base on how big the array is

Examples
O(1): Searching for the first element in the array, Array[4] = 1 run, Array[1000000] = 1 run
O(n): Array[4] = 4 runs, Array[16] = 16 runs, Array[100] = 100 runs
O(log n): Array[4] = 3 runs, Array[16] = 5 runs, Array[100] = 7 runs

Sort Examples
Bubble Sort = O(n^2): Array[4] = 16 runs, Array[16] = 256 runs, Array[100] = 10000 runs
*/

#include <iostream>
#include <chrono>
#include <stdlib.h>
#define NOMINMAX
#include <Windows.h>
#include <stdio.h>

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
uint32_t GetNanoseconds();
uint32_t GetMilliseconds();

// Sorting functions
void BubbleSort(int arr[], int arraySize);
void SelectionSort(int arr[], int arraySize);
void InsertionSort(int arr[], int arraySize);
void QuickSort(int arr[], int low, int high, int& comparisons);

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
		cout << "3. CHALLENGE: Find Path" << endl;
		cout << "6. Compare All Sorts" << endl;
		cout << "7. Compare All Searches" << endl;
		cout << "9. Tower of Hanoi" << endl;
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
			//
			break;
		case 6:
		{
			srand((unsigned int)time(nullptr));

			// bubble
			int bubbleDataset[ARRAY_SIZE];
			FillArray(bubbleDataset, ARRAY_SIZE);
			uint32_t bubbleStartNS = GetNanoseconds();
			BubbleSort(bubbleDataset, ARRAY_SIZE);
			uint32_t bubbleEndNS = GetNanoseconds();

			// selection
			int selectionDataset[ARRAY_SIZE];
			FillArray(selectionDataset, ARRAY_SIZE);
			uint32_t selectionStartNS = GetNanoseconds();
			SelectionSort(bubbleDataset, ARRAY_SIZE);
			uint32_t selectionEndNS = GetNanoseconds();

			// insertion
			int insertionDataset[ARRAY_SIZE];
			FillArray(insertionDataset, ARRAY_SIZE);
			uint32_t insertionStartNS = GetNanoseconds();
			InsertionSort(insertionDataset, ARRAY_SIZE);
			uint32_t insertionEndNS = GetNanoseconds();
			
			// quick
			int quickDataset[ARRAY_SIZE];
			FillArray(quickDataset, ARRAY_SIZE);
			uint32_t quickStartNS = GetNanoseconds();
			int comparisons = 0;
			QuickSort(quickDataset, 0, ARRAY_SIZE - 1, comparisons);
			uint32_t quickEndNS = GetNanoseconds();

			cout << endl;
			cout << "Bubble Sort took    " << (bubbleEndNS - bubbleStartNS) << "ns" << endl;
			cout << "Selection Sort took " << (selectionEndNS - selectionStartNS) << "ns" << endl;
			cout << "Insertion Sort took " << (insertionEndNS - insertionStartNS) << "ns" << endl;
			cout << "Quick Sort took     " << (quickEndNS - quickStartNS) << "ns" << endl;
			
			system("pause");
			break;
		}
		case 7:
		{
			srand((unsigned int)time(nullptr));
			int dataset[ARRAY_SIZE];
			FillArray(dataset, ARRAY_SIZE);
			BubbleSort(dataset, ARRAY_SIZE);

			int numToFind;
			cout << "Enter a number to find: ";
			while (true)
			{
				if (cin >> numToFind) break;
				else
				{
					cout << "Please enter a valid number: ";
					ClearCin();
				}
			}

			uint32_t linearStartNS = GetNanoseconds();
			int linearIndex = LinearSearch(dataset, numToFind);
			uint32_t linearEndNS = GetNanoseconds();

			uint32_t binaryStartNS = GetNanoseconds();
			int binaryIndex = BinarySearch(dataset, 0, ARRAY_SIZE, numToFind);
			uint32_t binaryEndNS = GetNanoseconds();

			cout << numToFind << " was " << (binaryIndex == -1 ? "NOT " : "") << "found in the array." << endl;

			cout << "Linear Search took " << (linearEndNS - linearStartNS) << "ns" << endl;
			cout << "Binary Search took " << (binaryEndNS - binaryStartNS) << "ns" << endl;

			system("pause");
			break;
		}
		case 9:
		{
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
			uint32_t startMilliseconds = GetMilliseconds();
			TowerOfHanoi(numDisks);
			uint32_t endMilliseconds = GetMilliseconds();
			cout << "Tower of Hanoi solved in " << (endMilliseconds - startMilliseconds) << "ms." << endl;
			system("pause");
			break;
		}
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
		srand((unsigned int)time(nullptr));
		int dataset[ARRAY_SIZE];
		FillArray(dataset, ARRAY_SIZE);
		uint32_t startMilliseconds = 0;
		uint32_t endMilliseconds = 0;

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
			DisplayArray(dataset);
			startMilliseconds = GetMilliseconds();
			BubbleSort(dataset, ARRAY_SIZE);
			endMilliseconds = GetMilliseconds();
			DisplayArray(dataset);
			break;
		case 2:
			cout << "Selection Sort" << endl << endl;
			cout << "BEFORE on top, AFTER on bottom" << endl << endl;
			DisplayArray(dataset);
			startMilliseconds = GetMilliseconds();
			SelectionSort(dataset, ARRAY_SIZE);
			endMilliseconds = GetMilliseconds();
			DisplayArray(dataset);
			break;
		case 3:
			cout << "Insertion Sort" << endl << endl;
			cout << "BEFORE on top, AFTER on bottom" << endl << endl;
			DisplayArray(dataset);
			startMilliseconds = GetMilliseconds();
			InsertionSort(dataset, ARRAY_SIZE);
			endMilliseconds = GetMilliseconds();
			DisplayArray(dataset);
			break;
		case 4:
		{
			cout << "Quick Sort" << endl << endl;
			cout << "BEFORE on top, AFTER on bottom" << endl << endl;
			DisplayArray(dataset);
			int comparisons = 0;
			startMilliseconds = GetMilliseconds();
			QuickSort(dataset, 0, ARRAY_SIZE - 1, comparisons);
			endMilliseconds = GetMilliseconds();
			cout << "Quick Sort comparisons: " << comparisons << endl;
			DisplayArray(dataset);
			break;
		}
		default:
			break;
		}

		if (!done)
		{
			cout << "Sort took " << (endMilliseconds - startMilliseconds) << "ms" << endl << endl;
			system("pause");
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
		srand((unsigned int)time(nullptr));
		int dataset[ARRAY_SIZE];
		FillArray(dataset, ARRAY_SIZE);
		BubbleSort(dataset, ARRAY_SIZE);
		uint32_t startMilliseconds = 0;
		uint32_t endMilliseconds = 0;

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

			startMilliseconds = GetMilliseconds();
			int index = LinearSearch(dataset, search);
			endMilliseconds = GetMilliseconds();

			if (index == -1) cout << search << " is not in the array." << endl << endl;
			else cout << search << " was found at index " << index << "." << endl << endl;

			cout << "Full array below: " << endl;
			DisplayArray(dataset, index);
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

			startMilliseconds = GetMilliseconds();
			int index = BinarySearch(dataset, 0, ARRAY_SIZE, search);
			endMilliseconds = GetMilliseconds();

			if (index == -1) cout << search << " is not in the array." << endl << endl;
			else cout << search << " was found at index " << index << "." << endl << endl;

			cout << "Full array below: " << endl;
			DisplayArray(dataset, index);
			break; }
		default:
			break;
		}

		if (!done)
		{
			cout << "Sort took " << (endMilliseconds - startMilliseconds) << "ms" << endl << endl;
			system("pause");
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

uint32_t GetNanoseconds()
{
	using namespace std::chrono;
	return static_cast<uint32_t>(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
}

uint32_t GetMilliseconds()
{
	using namespace std::chrono;
	return GetNanoseconds() / 1000000;
}

/***************************************************************
**************************** SORTS *****************************
****************************************************************/
void BubbleSort(int arr[], int arraySize)
{
	int comparisons = 0;

	for (int pass = 0; pass < arraySize; ++pass)
	{
		for (int i = 0; i < arraySize - 1; ++i)
		{
			comparisons += 1;

			if (arr[i] > arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
			}
		}
	}

	cout << "Bubble Sort comparisons: " << comparisons << endl;
}

void SelectionSort(int arr[], int arraySize)
{
	int comparisons = 0;

	for (int i = 0; i < arraySize; i++)
	{
		int smallestNum = arr[i];

		for (int secondIndex = i; secondIndex < arraySize; secondIndex++)
		{
			comparisons += 1;

			if (arr[secondIndex] < smallestNum)
			{
				arr[i] = arr[secondIndex];
				arr[secondIndex] = smallestNum;
				smallestNum = arr[i];
			}
		}
	}

	cout << "Selection Sort comparisons: " << comparisons << endl;
}

void InsertionSort(int arr[], int arraySize)
{
	int comparisons = 0;

	for (int i = 1; i < arraySize; i++)
	{
		int temp = arr[i];
		int prevIndex = i - 1;

		while (prevIndex >= 0 && temp <= arr[prevIndex])
		{
			comparisons += 1;
			arr[prevIndex + 1] = arr[prevIndex];
			prevIndex = prevIndex - 1;
		}

		arr[prevIndex + 1] = temp;
	}

	cout << "Insertion Sort comparisons: " << comparisons << endl;
}

void QuickSort(int arr[], int low, int high, int& comparisons)
{
	if (low < high) {
		comparisons += 1;

		// get pivot
		int pivot = QuickSortPartition(arr, low, high);

		// repeat before pivot
		QuickSort(arr, low, pivot - 1, comparisons);

		// repeat after pivot
		QuickSort(arr, pivot + 1, high, comparisons);
	}
}

/***************************************************************
*************************** SEARCHES ***************************
****************************************************************/
int LinearSearch(int arr[], int valueToFind)
{
	int comparisons = 0;
	int index = -1;

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		comparisons += 1;

		if (arr[i] == valueToFind)
		{
			index = i;
			break;
		}
	}

	cout << "Linear Search comparisons: " << comparisons << endl;

	return index;
}

int BinarySearch(int arr[], int low, int high, int searchKey)
{
	int comparisons = 0;
	int index = -1;

	while (low <= high)
	{
		comparisons += 1;

		int middle = (low + high) / 2;

		if (searchKey == arr[middle])
		{
			index = middle;
			break;
		}
		else if (searchKey < arr[middle]) high = middle - 1;
		else low = middle + 1;
	}

	cout << "Binary Search comparisons: " << comparisons << endl;

	return index;
}

/***************************************************************
************************ TOWER OF HANOI ************************
****************************************************************/
void SolveTowerOfHanoi(int numDiscs, int fromStack, int toStack, int extraStack, int& numMoves)
{
	if (numDiscs == 0) return;
	SolveTowerOfHanoi(numDiscs - 1, fromStack, extraStack, toStack, numMoves);
	printf("Moving disc %d from stack %d to %d.\n", numDiscs, fromStack, toStack);
	SolveTowerOfHanoi(numDiscs - 1, extraStack, toStack, fromStack, numMoves);
	numMoves += 1;
}

void TowerOfHanoi(int numDiscs)
{
	int numMoves = 0;
	SolveTowerOfHanoi(numDiscs, 1, 3, 2, numMoves);
	cout << "Number of moves made: " << numMoves << endl;
}