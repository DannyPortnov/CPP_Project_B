#ifndef GO_H
#define GO_H

#include "Slot.h"
class Go : public Slot
{
public:
	Go(int index, const string& name);
	bool play(Player* p);
	~Go();
	string get_name() const;
	//void print_slot() const;
private:
	string m_name;
};
#endif

