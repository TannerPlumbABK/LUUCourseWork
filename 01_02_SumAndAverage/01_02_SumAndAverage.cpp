#include <iostream>

using namespace std;

#define SUM_AVG_MAX_COUNT 3

float GetSum(float nums[SUM_AVG_MAX_COUNT]);
float GetAverage(float sum);

int main()
{
	float nums[SUM_AVG_MAX_COUNT];

	cout << "Enter " << SUM_AVG_MAX_COUNT << " numbers" << endl;

	for (int i = 0; i < SUM_AVG_MAX_COUNT; i++) {
		cout << "Number " << i + 1 << ": ";

		while (true)
		{
			if (cin >> nums[i]) break;
			else
			{
				cout << endl << "Please enter a number: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
	}
	cout << endl;

	cout << "Sum: " << GetSum(nums) << endl;
	cout << "Average: " << GetAverage(GetSum(nums)) << endl;
}

float GetSum(float nums[SUM_AVG_MAX_COUNT])
{
	float sum = 0;

	for (int i = 0; i < SUM_AVG_MAX_COUNT; i++)
	{
		sum += nums[i];
	}

	return sum;
}

float GetAverage(float sum)
{
	return sum / SUM_AVG_MAX_COUNT;
}