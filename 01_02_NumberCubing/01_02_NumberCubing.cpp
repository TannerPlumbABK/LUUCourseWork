#include <iostream>

using namespace std;

float getNumberCubed(float num);

int main()
{
	float num;

	cout << "Enter a number to be cubed: ";

	for (;;)
	{
		if (cin >> num)
		{
			break;
		}
		else
		{
			cout << endl << "Please enter a number: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	float cubed = getNumberCubed(num);

	cout << num << " cubed is " << cubed << endl;
}

float getNumberCubed(float num)
{
	return num * num * num;
}