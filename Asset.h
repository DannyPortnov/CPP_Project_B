#ifndef ASSET_H
#define ASSET_H
#include "Slot.h"
#include "string"
using namespace std;

#define min_price 50
#define min_rental 300
#define price_range 100
#define rental_range 500 //46
//#include "Player.h"
class Asset : public Slot
{
public:
	Asset(int index,const string& city, const string& asset_name);
	/*Asset(const Asset& other_asset);*/
	~Asset();
	const string& get_city() const;
	string get_name() const; //isnt const & because of definition by Yael 
	int get_price_for_asset() const;
	int get_rental() const;
	const Player* get_owner() const;
	void set_owner(const Player* owner); 
	bool play(Player* p);
	/*Asset& operator=(const Asset& other_asset);*/
private:
	const string m_city;
	const string m_asset_name;
	int m_price_for_asset;
	int m_rental;
	const Player* m_owner;
};
#endif

