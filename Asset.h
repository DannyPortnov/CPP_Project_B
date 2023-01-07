#ifndef ASSET_H
#define ASSET_H
#include "Slot.h"
#include "string"
using namespace std;

class Player;
class Asset : public Slot
{
public:
	Asset(int index,const string& city, const string& asset_name, int price_for_asset, int rental);
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

