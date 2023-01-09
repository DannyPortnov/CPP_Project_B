#include "Jail.h"

Jail::Jail(int index, const string& name) : Slot(index), m_name(name) {}

bool Jail::play(Player* p)
{
	cout << "You're In Jail LOL! Wait 1 Turn" << endl;
	return true;
}

string Jail::get_name() const
{
	return m_name;
}

