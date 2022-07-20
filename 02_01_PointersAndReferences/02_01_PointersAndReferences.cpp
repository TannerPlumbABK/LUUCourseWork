#include <iostream>

using namespace std;

int main()
{
	int a;
	int b;

	cout << "Enter two numbers" << endl;

	cout << "Number 1: ";
	for (;;)
	{
		if (cin >> a) { break; }
		else
		{
			cout << "Please enter a valid whole number." << endl;
			cout << "Number 1: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	cout << "Number 2: ";
	for (;;)
	{
		if (cin >> b) { break; }
		else
		{
			cout << "Please enter a valid whole number." << endl;
			cout << "Number 2: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	cout << endl;

	int* ptrA = &a;
	int* ptrB = &b;

	cout << "You Entered:" << endl;
	cout << "Number 1: " << *ptrA << endl;
	cout << "Number 2: " << *ptrB << endl;
}