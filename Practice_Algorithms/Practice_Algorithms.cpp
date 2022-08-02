#include <iostream>
#include <map>
#include <string>

using namespace std;

struct Item
{
	int id;
	string name;
};

void fillItemNames(map<int, string>& itemMap)
{
	itemMap[4] = "Super Mega Dagger Destruction";
	

	itemMap[6] = "Weak Dagger";
}

int main()
{
	map<int, string> itemNamesById;
	fillItemNames(itemNamesById);

	cout << itemNamesById[4] << endl;

	map<int, map<int, string>> effects;

	effects[4][1] = "Burn target.";

	cout << effects[4][1] << endl;
}