#include <iostream>

using namespace std;

class Animal
{
public:
    virtual void MakeNoise() { }
};

class Pig : public Animal
{
public:
    virtual void MakeNoise() override
    {
        cout << "Oink" << endl;
    }
};

class Dog : public Animal
{
public:
    virtual void MakeNoise() override
    {
        cout << "Woof" << endl;
    }
};

int main()
{
    Pig pig;
    Dog dog;

    Animal* animal;

    animal = &pig;
    animal->MakeNoise();

    animal = &dog;
    animal->MakeNoise();
}