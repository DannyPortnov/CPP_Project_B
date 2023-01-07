#include "Slot.h"


Slot::Slot(int index) : m_index(index) {
	if (index > max_slot_index || index < min_slot_index) {
		stringstream ss;
		ss << "Exception: index " << to_string(index) << " out of range. Has to be between "
			<< to_string(max_slot_index) << " and " << to_string(max_slot_index) << endl;
		throw(ss);
	}
}

