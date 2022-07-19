#include <iostream>

using namespace std;

#define SUM_AVG_MAX_COUNT 3

float getSum(float nums[SUM_AVG_MAX_COUNT]);
float getAverage(float sum);

int main()
{
	float nums[SUM_AVG_MAX_COUNT];

	cout << "Enter " << SUM_AVG_MAX_COUNT << " numbers" << endl;

	for (int i = 0; i < SUM_AVG_MAX_COUNT; i++) {
		cout << "Number " << i + 1 << ": ";

		for (;;)
		{
			if (cin >> nums[i])
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
	}
	cout << endl;

	float sum = getSum(nums);
	float average = getAverage(sum);

	cout << "Sum: " << sum << endl;
	cout << "Average: " << average << endl;
}

float getSum(float nums[SUM_AVG_MAX_COUNT])
{
	float sum = 0;

	for (int i = 0; i < SUM_AVG_MAX_COUNT; i++)
	{
		sum += nums[i];
	}

	return sum;
}

float getAverage(float sum)
{
	return sum / SUM_AVG_MAX_COUNT;
}