#include "Jail.h"

Jail::Jail(int index, const string& name) : Slot(index), m_name(name) {}

Jail::~Jail()
{
}

inline bool Jail::play(Player* p)
{
	cout << m_name << endl;
	return true;
}

inline string Jail::get_name() const
{
	return "Jail";
}

