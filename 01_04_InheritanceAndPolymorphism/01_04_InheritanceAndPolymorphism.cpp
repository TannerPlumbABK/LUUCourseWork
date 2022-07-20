#include "Player.h"
#include "Enemy.h"

#include <iostream>

using namespace std;

int main()
{
	Player player = Player(5, 2, 1);
	Enemy enemy = Enemy(1, 5, 9);

	player.OutputInfo();
	cout << endl;

	enemy.OutputInfo();
	cout << endl;
}