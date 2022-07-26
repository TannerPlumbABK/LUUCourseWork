#include <iostream>

using namespace std;

#define NUM_NUMBERS 5

int GetBiggestNumber(int numbers[NUM_NUMBERS]);

int main()
{
    int numbers[NUM_NUMBERS];

    cout << "Enter 5 whole numbers to determine which is the largest." << endl;

    for (int i = 0; i < NUM_NUMBERS; i++)
    {
        cout << "Number " << i + 1 << ": ";

        while (true)
        {
            if (cin >> numbers[i]) break;
            else
            {
                cout << endl << "Please enter a valid whole number." << endl;
                cout << "Number " << i + 1 << ": ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    cout << "The highest number you entered is: " << GetBiggestNumber(numbers) << endl;
}

int GetBiggestNumber(int numbers[NUM_NUMBERS])
{
    int highestNumber = numbers[0];

    for (int i = 0; i < NUM_NUMBERS; i++)
    {
        if (numbers[i] > highestNumber)
        {
            highestNumber = numbers[i];
        }
    }

    return highestNumber;
}