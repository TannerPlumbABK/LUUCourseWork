#include <iostream>

using namespace std;

bool IsLeapYear(int year);

int main()
{
    int year;

    cout << "Enter a year: ";

    while (true)
    {
        if (cin >> year) break;
        else
        {
            cout << endl << "Please enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cout << year << " is " << (IsLeapYear(year) ? "" : "not ") << "a leap year." << endl;
}

bool IsLeapYear(int year)
{
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}