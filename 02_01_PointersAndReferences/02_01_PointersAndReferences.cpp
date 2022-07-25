#include <iostream>
#include <string>

using namespace std;

void GetInput(int& a, int& b);
void DisplayInput(int* a, int* b);
void CinError(string error);

int main()
{
	int a, b;
	GetInput(a, b);

	int* ptrA = &a;
	int* ptrB = &b;
	DisplayInput(ptrA, ptrB);
}

void CinError(string error)
{
	cout << error;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void GetInput(int& a, int& b)
{
	cout << "Enter two numbers" << endl;

	cout << "Number 1: ";
	while (true)
	{
		if (cin >> a) break;
		else CinError("Please enter a valid whole number.\nNumber 1: ");
	}

	cout << "Number 2: ";
	while (true)
	{
		if (cin >> b) break;
		else CinError("Please enter a valid whole number.\nNumber 2: ");
	}

	cout << endl;
}

void DisplayInput(int* a, int* b)
{
	cout << "You Entered:" << endl;
	cout << "Number 1: " << *a << " (" << a << ")" << endl;
	cout << "Number 2: " << *b << " (" << b << ")" << endl;
}