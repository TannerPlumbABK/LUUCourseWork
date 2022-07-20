#include <iostream>

using namespace std;

void Swap(int* pNumber1, int* pNumber2);
void Swap(int& number1, int& number2);

int main()
{
	int a = 10;
	int b = 20;
	cout << "A: " << a << endl;
	cout << "B: " << b << endl;
	cout << endl;

	Swap(a, b);
	cout << "A: " << a << endl;
	cout << "B: " << b << endl;
	cout << endl;

	Swap(&a, &b);
	cout << "A: " << a << endl;
	cout << "B: " << b << endl;
	cout << endl;
}

void Swap(int* pNumber1, int* pNumber2)
{
	int temp = *pNumber1;
	*pNumber1 = *pNumber2;
	*pNumber2 = temp;
}

void Swap(int& number1, int& number2)
{
	int temp = number1;
	number1 = number2;
	number2 = temp;
}