#ifndef GO_H
#define GO_H

#include "Slot.h"
class Go : public Slot
{
public:
	Go(int index, const string& name);
	bool play(Player* p);
	string get_name() const;
private:
	string m_name;
};
#endif

