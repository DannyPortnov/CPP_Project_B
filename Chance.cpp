#include "Chance.h"
#include "Player.h"
#include <cstdlib>

Chance::Chance(int index, const string& name, int sum) : Slot(index),
m_name(name), m_sum(sum) {}

Chance::~Chance()
{
}

bool Chance::play(Player* p)
{
	cout << m_name << endl;
	string action = "Have to pay";
	if (m_sum >= 0) {
		action = "Won";
	}
	cout << "You " << action << " " << abs(m_sum) << "$!" << endl;
	p->set_balance(m_sum);
	if (p->get_balance() < 0) { 
		cout << p->get_name() << " can't afford to pay tax." << endl;
		cout << "Game Over, " << p->get_name() << endl;
		return false;
	}
	cout << "You're new balance is: " << p->get_balance() << "$" << endl;
	return true;
}


inline string Chance::get_name() const
{
	return "Chance";
}
