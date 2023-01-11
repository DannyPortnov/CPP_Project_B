#define   _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "Board.h"
//#include "Slot.h"
#include "Player.h"
#include <string>
#include <iostream>
using namespace std;

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

void run_monopoly() {
	Board monopoly;
	cout << monopoly;
	Player players[2] = { Player("Danny",&monopoly),Player("Niv",&monopoly) };
	monopoly.play(players);
}

#define DebugMode true

int main()
{
#if DebugMode
	do
	{
		run_monopoly();
		cout << "Memory Leaks: " << _CrtDumpMemoryLeaks() << endl;
	} while (!_CrtDumpMemoryLeaks());
#else 
	run_monopoly();
	cout << "Memory Leaks: " << _CrtDumpMemoryLeaks() << endl; 
#endif // DebugMode

	return 0;
}
