#include <iostream>

using namespace std;

void DisplayFactors(int num);

int main()
{
    int num;

    cout << "Enter a positive whole number: ";

    while (true)
    {
        if (cin >> num && num > 0) break;
        else
        {
            cout << endl << "Please enter a valid positive whole number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    DisplayFactors(num);
}

void DisplayFactors(int num)
{
    for (int i = 1; i <= num; i++)
    {
        if (num % i == 0)
        {
            cout << i << endl;
        }
    }
}