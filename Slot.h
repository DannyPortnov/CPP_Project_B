#ifndef SLOT_H
#define SLOT_H

#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

#define min_slot_index 1
#define max_slot_index 18
#include "Player.h"
class Slot
{
public:
	Slot(int index);
	//~Slot(); //no destructor is required in base class
	virtual bool play(Player* p) = 0;
	virtual string get_name() const = 0;
private:
	int m_index;
};

#endif

