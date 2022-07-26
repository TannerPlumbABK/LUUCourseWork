#include <iostream>

using namespace std;

float GetNumberCubed(float num);

int main()
{
	float num;

	cout << "Enter a number to be cubed: ";

	while (true)
	{
		if (cin >> num) break;
		else
		{
			cout << endl << "Please enter a number: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	float cubed = GetNumberCubed(num);

	cout << num << " cubed is " << cubed << endl;
}

float GetNumberCubed(float num)
{
	return num * num * num;
}