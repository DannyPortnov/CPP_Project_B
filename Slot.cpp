#include "Slot.h"


Slot::Slot(int index) : m_index(index) {
	if (index > max_slot_index || index < min_slot_index) {
		stringstream ss;
		ss << "Exception: index " << to_string(index) << " out of range. Has to be between "
			<< to_string(max_slot_index) << " and " << to_string(max_slot_index) << endl;
		throw(ss);
	}
}

Slot::~Slot()
{
}

inline int Slot::get_index() const
{
	return m_index;
}

//for each inherited class prints the slot's name (except for Asset, which overrides it)
ostream& operator<<(ostream& os, const Slot* s)
{
	os << s->get_name();
	return os;
}
