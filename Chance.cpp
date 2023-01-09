#include "Chance.h"

Chance::Chance(int index, const string& name, int sum) : Slot(index),
m_name(name), m_sum(sum) {}

bool Chance::play(Player* p)
{
	string action = "Have to pay";
	if (m_sum >= 0) {
		action = "Won";
	}
	cout << "You " << action << " Dollars!"; 
	p->set_balance(m_sum);
	if (p->get_balance() < 0) { //todo: change later so that set_balance returns bool maybe
		return true;
	}
	return false;
}

string Chance::get_name() const
{
	return m_name;
}

