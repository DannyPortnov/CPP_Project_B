#include "Asset.h"
#include "Player.h"

Asset::Asset(int index, const string& city, const string& asset_name)
	: Slot(index), m_city(city), m_asset_name(asset_name),
	m_price_for_asset(rand() % price_range + min_price),
	m_rental(rand() % rental_range + min_rental), m_owner(nullptr) {}


Asset::~Asset()
{
}

inline const string& Asset::get_city() const
{
	return m_city;
}

inline string Asset::get_name() const
{
	return m_asset_name;
}

int Asset::get_price_for_asset() const
{
	return m_price_for_asset;
}

inline int Asset::get_rental() const
{
	return m_rental;
}

inline const Player* Asset::get_owner() const
{
	return m_owner;
}

void Asset::set_owner(const Player* owner) //const pointers means the data is const, not the pointer!
{
	m_owner = owner;
}
#define DebugMode true

bool Asset::play(Player* p) //can't be const either
{
	if (m_owner != nullptr && p != m_owner) {
		cout << "Pay " << m_rental << "$" << " to " << m_owner->get_name() << endl;
		return p->pay_rent(m_rental);
	}
	if (m_owner == nullptr) {
		char answer;
		cout << "Do you want to buy " << this << " for " << m_price_for_asset << "$?"
			<< " y - yes, any other key - no" << endl;
#if DebugMode
		answer = 'y';
#else
		cin >> answer;
#endif // DebugMode
		if (answer == 'y') {
			p->add_asset(this);
	}
}
	return true;
}

//Asset& Asset::operator=(const Asset& other_asset)
//{
//	Asset temp= Asset(other_asset);
//}

ostream& operator<<(ostream& os, const Asset* b)
{
	os << b->get_city() << ", " << b->get_name();
	return os;
}
