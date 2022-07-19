#include <iostream>

using namespace std;

int main()
{
    int year;

    cout << "Enter a year: ";

    for (;;)
    {
        if (cin >> year)
        {
            break;
        }
        else
        {
            cout << endl << "Please enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
    {
        cout << year << " is a leap year." << endl;
    }
    else
    {
        cout << year << " is not a leap year." << endl;
    }
}