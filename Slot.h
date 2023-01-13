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
class Player;
class Slot
{
public:
	Slot(int index);
	virtual ~Slot(); 
	virtual bool play(Player* p) = 0;
	virtual string get_name() const = 0;
	int get_index() const;
	friend ostream& operator<<(ostream& os, const Slot* s);
private:
	int m_index;
};

#endif

