#ifndef CHANCE_H
#define CHANCE_H
#include "Slot.h"

class Chance : public Slot
{
private:
	string m_name;
	int m_sum;
public:
	Chance(int index, const string& name, int sum);
	~Chance();
	bool play(Player* p);
	string get_name() const;
};

//unsigned abs(int wow);
#endif


