#include "Board.h"
//#include "Slot.h"
#include "Player.h"
#include <string>
#include <iostream>
using namespace std;


int main()
{

	Board monopoly;	
	cout << monopoly;
	Player players[2] = { Player("Danny",&monopoly),Player("Niv",&monopoly) };
	monopoly.play(players);
	return 0;

}
