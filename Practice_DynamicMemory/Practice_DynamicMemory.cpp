#include <iostream>

using namespace std;

// notes
/*
* Every time you use the "new" keyword, expect to need to have a matching "delete"
* With dynamic memory, be sure to remember to set set the pointer to "nullptr" when done
* 
* Arrays must be deleted with delete[] instead of just delete
*/

int* CreateIntArray(int size);
void Populate(int* pArray, int size);
void DisplayArray(int* pArray, int size);

int main()
{
	// GOOD EXAMPLE
	int* pInt = new int{ 10 };
	cout << *pInt << endl;
	delete pInt;
	pInt = nullptr;

	// BAD EXAMPLE
	float* pFloat = new float{ 20.5f }; // <-- THIS IS NO LONGER REACHABLE
	pFloat = new float{ 30.5f }; // BECAUSE OF THIS NEW ASSIGNMENT
	delete pFloat;
	pFloat = nullptr;

	// GOOD EXAMPLE - ARRAY
	int* pIntArray = new int[5];
	delete[] pIntArray;
	pIntArray = nullptr;

	cout << endl;

	// DYNAMIC ARRAY SIZE EXAMPLE
	int size;
	cout << "Size of the array: ";
	cin >> size;

	int* pArray = CreateIntArray(size);

	Populate(pArray, size);
	DisplayArray(pArray, size);

	delete pArray;
	pArray = nullptr;
}

int* CreateIntArray(int size)
{
	int* ptr = new int[size];
	return ptr;
}

void Populate(int* pArray, int size)
{
	cout << "Input Values" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "Item " << i + 1 << ": ";
		cin >> pArray[i];
	}
	cout << endl;
}

void DisplayArray(int* pArray, int size)
{
	cout << "Your Values" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "Item " << i + 1 << ": " << pArray[i] << endl;
	}
	cout << endl;
}