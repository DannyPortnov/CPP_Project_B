#ifndef ASSET_H
#define ASSET_H
#include "Slot.h"
#include "string"
using namespace std;

#define min_price 50
#define min_rental 5
#define price_range 101
#define rental_range 46 
class Asset : public Slot
{
public:
	Asset(int index, const string& city, const string& asset_name);
	~Asset();
	const string& get_city() const;
	string get_name() const; 
	int get_price_for_asset() const;
	int get_rental() const;
	const Player* get_owner() const;
	void set_owner(const Player* owner);
	bool play(Player* p);
	friend ostream& operator<<(ostream& os, const Asset* b);
private:
	const string m_city;
	const string m_asset_name;
	int m_price_for_asset;
	int m_rental;
	const Player* m_owner;
};

#endif

