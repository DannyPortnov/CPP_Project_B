#include "Jail.h"

Jail::Jail(int index, const string& name) : Slot(index), m_name(name) {}

bool Jail::play(Player* p)
{
	cout << "You're in jail lol! sucker" << endl;
	return true;
}

string Jail::get_name() const
{
	return m_name;
}

