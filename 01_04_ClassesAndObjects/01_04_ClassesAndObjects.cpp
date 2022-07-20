#include <iostream>
#include "Player.h"

using namespace std;

int main()
{
    Player player;

    player.DisplayLevel();
    player.DisplayPosition();

    player.LevelUp();
    player.SetPosition(3, 12);

    player.DisplayLevel();
    player.DisplayPosition();

    player.SetLevel(35);
    player.DisplayLevel();
}