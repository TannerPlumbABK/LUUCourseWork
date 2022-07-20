#include <iostream>

using namespace std;

int main()
{
    int num;

    cout << "Enter a positive whold number: ";

    for (;;)
    {
        if (cin >> num && num > 0)
        {
            break;
        }
        else
        {
            cout << endl << "Please enter a valid positive whole number: ";
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