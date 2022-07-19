#include <iostream>

using namespace std;

#define NUM_NUMBERS 5

int main()
{
    int numbers[NUM_NUMBERS];
    int highestNumber;

    cout << "Enter 5 whole numbers to determine which is the largest." << endl;

    for (int i = 0; i < NUM_NUMBERS; i++)
    {
        cout << "Number " << i + 1 << ": ";

        for (;;)
        {
            if (cin >> numbers[i])
            {
                break;
            }
            else
            {
                cout << endl << "Please enter a valid whole number." << endl;
                cout << "Number " << i + 1 << ": ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    highestNumber = numbers[0];

    cout << "Out of the following numbers: ";
    for (int i = 0; i < NUM_NUMBERS; i++)
    {
        cout << numbers[i];

        if (i < NUM_NUMBERS - 1)
        {
            cout << ", ";
        }

        if (numbers[i] > highestNumber)
        {
            highestNumber = numbers[i];
        }
    }
    cout << endl;

    cout << "The highest number is: " << highestNumber << endl;
}