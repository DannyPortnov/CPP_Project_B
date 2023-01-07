#ifndef SLOT_H
#define SLOT_H

#include <string>

using namespace std;

#define min_slot_num 1
#define max_slot_num 18
class Player;
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

