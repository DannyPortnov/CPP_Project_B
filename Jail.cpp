#include "Jail.h"

Jail::Jail(int index, const string& name) : Slot(index), m_name(name) {}

Jail::~Jail()
{
}

bool Jail::play(Player* p)
{
	cout << m_name << endl;
	return true;
}

string Jail::get_name() const
{
	return "Jail";
}

