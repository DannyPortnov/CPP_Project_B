#include "Board.h"
//#include "Slot.h"
#include "Player.h"
#include <string>
#include <iostream>
using namespace std;


int main()
{

	Board monopoly;	
	Board monopoly2;	
	cout << monopoly;
	Player danny("Danny", &monopoly);
	Player niv("niv", &monopoly);
	Player players[2] = { Player("Danny",&monopoly),Player("Niv",&monopoly) };
	Player players2[2] = { Player("sup",&monopoly),Player("test",&monopoly) };
	//monopoly.play(players);
	return 0;

}
