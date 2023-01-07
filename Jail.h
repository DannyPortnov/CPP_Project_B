#pragma once
#include "Slot.h"
class Jail : public Slot
{
private:
	string m_name;
public:
	Jail(int index, const string& name);
	bool play(Player* p);
	string get_name() const;
};

