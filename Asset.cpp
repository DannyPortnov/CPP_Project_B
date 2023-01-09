#include "Asset.h"
#include "Player.h"

Asset::Asset(int index, const string& city, const string& asset_name)
	: Slot(index), m_city(city), m_asset_name(asset_name),
	m_price_for_asset(rand() % price_range + min_price),
	m_rental(rand() % rental_range + min_rental), m_owner(nullptr) {}

Asset::Asset(const Asset& other_asset) : Slot(other_asset.get_index()), m_city(other_asset.get_city()), m_asset_name(other_asset.get_city()),
m_price_for_asset(other_asset.get_price_for_asset()),
m_rental(other_asset.get_rental()), m_owner(other_asset.get_owner()) {}

Asset::~Asset()
{
	delete m_owner;
}

const string& Asset::get_city() const
{
	return m_city;
}

string Asset::get_name() const
{
	return m_asset_name;
}

int Asset::get_price_for_asset() const
{
	return m_price_for_asset;
}

int Asset::get_rental() const
{
	return m_rental;
}

Player* Asset::get_owner() const
{
	return m_owner;
}

void Asset::set_owner(Player* owner) //check if possible ref here
{
	m_owner = owner;
}

bool Asset::play(Player* p)
{
	if (p != nullptr && p != m_owner) {
		return p->pay_rent(m_rental);
	}
	if (p == nullptr) {
		char answer;
		cout << "Do you want to buy " << m_asset_name << " for " << m_price_for_asset << " Dollars?"
			<< " y/n" << endl;
		cin >> answer;
		if (answer == 'y') {
			p->add_asset(this); //todo: checl if (*this) is ok- we need to return a pointer so i changed to (this)
		}
	}
	return true;
}

//Asset& Asset::operator=(const Asset& other_asset)
//{
//	Asset temp= Asset(other_asset);
//}
