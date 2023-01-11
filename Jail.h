#ifndef JAIL_H
#define JAIL_H
#include "Slot.h"
class Jail : public Slot
{
private:
	string m_name;
public:
	Jail(int index, const string& name);
	~Jail();
	bool play(Player* p);
	string get_name() const;
};
#endif

