#include <iostream>

using namespace std;

int main()
{
    int num;

    cout << "Enter a number: ";

    for (;;)
    {
        if (cin >> num)
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

    for (int i = 2; i <= num; i++)
    {
        if (num % i == 0)
        {
            cout << i << endl;
        }
    }
}