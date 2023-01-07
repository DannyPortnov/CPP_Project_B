#ifndef ASSET_H
#define ASSET_H
#include "Slot.h"
#include "string"
using namespace std;

#define min_price 50
#define min_rental 5
#define price_range 100
#define rental_range 45

class Player;
class Asset : public Slot
{
public:
	Asset(int index,const string& city, const string& asset_name);
	const string& get_city() const;
	string get_name() const;
	int get_price_for_asset() const;
	int get_rental() const;
	const Player* get_owner() const; //todo: check if possible to use ref here
	void set_owner(Player*& owner); //todo: check if possible to use const Player
	bool play(Player* p) const;
private:
	string m_city;
	string m_asset_name;
	int m_price_for_asset;
	int m_rental;
	Player* m_owner;
};
#endif

